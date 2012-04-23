#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

// Bitsets
#include "ewah.h"
#include "boolarray.h"

// Hashing
#include "murmur3.h"

typedef VALUE (ruby_method)(...);

typedef struct hyperbuilder {
  short bits;
  uword32 registerCount;
  BoolArray<uword64> *registers;
} HyperBuilder;

typedef struct hyperestimator {
  short bits;
  EWAHBoolArray<uword64> *registers;
} HyperEstimator;

// Register Helpers
extern "C" void hyperbuilder_printBits(uword64 x) {
  for(short i = sizeof(x) * 8; i >= 0; i--) {
    cout << ((x >> i) & 0x01);
  }
  cout << endl;
}

extern "C" void hyperbuilder_set_register(BoolArray<uword64> *registers, uword32 position, uword64 value) {
  uword64 maskBits = 0x1f;
  uword32 bucketPos = position / 12;
  uword32 shift = 5 * (position - (bucketPos * 12));
  // cout << "Setting register " << bucketPos << " at shift " << shift << " to value " << value << endl;
  // cout << "BEFORE ";
  // hyperbuilder_printBits(registers->getWord(bucketPos));
  // cout << "MASK   ";
  // hyperbuilder_printBits(~(maskBits << shift));
  // cout << "VALUE  ";
  // hyperbuilder_printBits(value);
  // cout << "VALUE(S)";
  // hyperbuilder_printBits(value << shift);
  
  registers->setWord( bucketPos, (registers->getWord(bucketPos) & ~(maskBits << shift)) | (value << shift) );
  // cout << "AFTER  ";
  // hyperbuilder_printBits(registers->getWord(bucketPos));
}

extern "C" uword32 hyperbuilder_get_register(BoolArray<uword64> *registers, uword32 position) {
  uword64 maskBits = 0x1f;
  uword32 bucketPos = position / 12;
  uword32 shift = 5 * (position - (bucketPos * 12));
  // cout << "Getting register " << bucketPos << " at shift " << shift << endl;
  return (registers->getWord(bucketPos) & (maskBits << shift)) >> shift;
}

// Hashing and Calculations 
extern "C" uword64 hyperbuilder_clz(uword32 x) {
  uword32 zeros = 0;
  for (short msb = 8 * sizeof(x);
    !(x & (1ULL << msb)) && msb >= 0;
    --msb, ++zeros) {}
  
  return zeros;
}

extern "C" uword32 hyperbuilder_hash(VALUE element) {
  uword32 hash;
  uword32 seed = 23;
  MurmurHash3_x86_32(RSTRING(element)->ptr, RSTRING(element)->len, seed, &hash);
  return hash;
}

// Core API
extern "C" VALUE hyperbuilder_new(VALUE klass, VALUE bits) {
  HyperBuilder *builder = ALLOC(HyperBuilder);
  
  builder->bits = FIX2INT(bits);
  builder->registerCount = static_cast<uword32>(floor((pow(2, FIX2INT(bits)) / 12)) + 1);
  // cout << "Creating a new bool array with " << floor((pow(2, FIX2INT(bits)) / 12)) + 1 << " words" << endl;
  
  builder->registers = new BoolArray<uword64>(builder->registerCount * 64);
  
  // cout << "Registers now has size " << builder->registers->sizeInBits() << " bits" << endl;
  
  return Data_Wrap_Struct(klass, 0, free, builder);
}

extern "C" VALUE hyperbuilder_offer(VALUE self, VALUE item) {
  HyperBuilder *builder;
  Data_Get_Struct(self, HyperBuilder, builder);
  
  uword32 x = hyperbuilder_hash(item);
  uword32 j = x >> (32 - builder->bits);
  uword64 r = hyperbuilder_clz( (x << builder->bits) | (1 << (builder->bits - 1)) + 1 );
  
  uword32 registerValue = hyperbuilder_get_register(builder->registers, j);
  
  if(registerValue < r) {
    hyperbuilder_set_register(builder->registers, j, r);
    return Qtrue;
  } else {
    return Qfalse;
  }
}

// extern "C" VALUE hyperbuilder_estimator(VALUE self) {
//   // create a new estimator from our serialized self
//   return Qnil;
// }
// 
extern "C" VALUE hyperbuilder_serialize(VALUE self) {
  HyperBuilder *builder;
  Data_Get_Struct(self, HyperBuilder, builder);
  
  EWAHBoolArray<uword64> ewahBitset;
  for(uword32 i = 0; i < builder->registerCount; i++) {
    ewahBitset.add(builder->registers->getWord(i));
  }
  
  stringstream ss;
  ewahBitset.write(ss);
  return rb_str_new(ss.str().c_str(), ss.str().size());
}
// 
// extern "C" VALUE hyperbuilder_merge(VALUE args) {
//   // return a new hyperbuilder from merging a bunch of other ones
//   return Qnil;
// }

/*
 * HyperEstimator
 */

// extern "C" VALUE hyperestimator_new(VALUE klass, VALUE args) {
//   return Qnil;
// }
// 
// extern "C" VALUE hyperestimator_init(VALUE klass, VALUE args) {
//   return Qnil;
// }
// 
// extern "C" VALUE hyperestimator_merge(VALUE args) {
//   // return a new HyperEstimator by merging a bunch of other ones
//   return Qnil;
// }

// class function
// extern "C" VALUE hyperestimator_estimate(VALUE args) {
//   // merge args and then estimate
//   VALUE merged = hyperestimator_merge(args);
//   
//   // var r_sum = 0
//   // for(var j = 0; j < registers.count; j++) {
//   //   r_sum += Math.pow(2, (-1 * registers.get(j)))
//   // }
//   // 
//   // // for registerCount >= 128 (bits >= 7)
//   // var alpha_m = 0.7213 / (1 + 1.079 / registers.count)
//   // var estimate = alpha_m * Math.pow(registers.count, 2) * (1 / r_sum)
//   // 
//   // if(estimate <= (5.0/2.0) * registers.count) {
//   //   // Small Range Estimate
//   //   var zeros = 0.0
//   //   for(var z = 0; z < registers.count; z++) {
//   //     if(registers.get(z) == 0) { zeros++ }
//   //   }
//   //   return Math.round(registers.count * Math.log(registers.count / zeros))
//   // } else if(estimate <= (1.0/30.0) * Math.pow(2, 32)) {
//   //   // Intermedia Range Estimate
//   //   return Math.round(estimate)
//   // } else if(estimate > (1.0/30.0) * Math.pow(2, 32)) {
//   //   // Large Range Estimate
//   //   return Math.round( (Math.pow(-2, 32) * Math.log(1 - (estimate / Math.pow(2, 32)))) )
//   // }
//   
//   return Qnil;
// }

static VALUE rbHyperBuilder;
static VALUE rbHyperEstimator;
extern "C" void Init_hyperloglog() {
  rbHyperBuilder = rb_define_class("HyperBuilder", rb_cObject);
  rb_define_singleton_method(rbHyperBuilder, "new", (ruby_method*) &hyperbuilder_new, 1);

  rb_define_method(rbHyperBuilder, "offer", (ruby_method*) &hyperbuilder_offer, 1);
  // rb_define_method(rbHyperBuilder, "estimator", (ruby_method*) &hyperbuilder_estimator, 0);
  rb_define_method(rbHyperBuilder, "serialize", (ruby_method*) &hyperbuilder_serialize, 0);
  // rb_define_singleton_method(rbHyperBuilder, "merge", (ruby_method*) &hyperbuilder_merge, -2);

  // rbHyperEstimator = rb_define_class("HyperEstimator", rb_cObject);
  // rb_define_singleton_method(rbHyperEstimator, "new", (ruby_method*) &hyperestimator_new, 1);
  // rb_define_method(rbHyperBuilder, "initialize", (ruby_method*) &hyperestimator_init, 1);
  // rb_define_singleton_method(rbHyperEstimator, "estimate", (ruby_method*) &hyperestimator_estimate, -2);
}