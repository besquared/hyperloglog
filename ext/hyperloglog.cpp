#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ewah/ewah.h"
#include "murmur3/murmur3.h"

typedef VALUE (ruby_method)(...);

typedef struct hyperloglog {
  short bits;
  BoolArray<uword64> *registers;
} HyperLogLog;

// Register Helpers
extern "C" void hyperloglog_set_register(BoolArray<uword64> *registers, uword32 position, uword32 value) {
  uword32 bucketPos = position / 12;
  uword32 shift = 5 * (position - (bucketPos * 12));
  registers->setWord( position, static_cast<uword32>( (registers->getWord(bucketPos) & ~(0x1f << shift)) | (value << shift) ) );
}

extern "C" uword32 hyperloglog_get_register(BoolArray<uword64> *registers, uword32 position) {
  uword32 bucketPos = position / 12;
  uword32 shift = 5 * (position - (bucketPos * 12));
  return (registers->getWord(bucketPos) & (0x1f << shift)) >> shift;
}

// Hashing and Calculations 
extern "C" uword32 hyperloglog_clz(uword32 x) {
  if(x == 0) { return 0; }
  for(short i = sizeof(uword32); i >= 0; i--) {
    if(((x >> i) & 0x01) == 1) { return sizeof(uword32) - i; }
  }
  throw "Could not find a count of leading zeros.";
}

extern "C" uword32 hyperloglog_hash(VALUE element) {
  uword32 hash;
  uword32 seed = 23;
  MurmurHash3_x86_32(RSTRING(element)->ptr, RSTRING(element)->len, seed, &hash);
  return hash;
}

// Core API
extern "C" VALUE hyperloglog_offer(VALUE self, VALUE item) {
  // We can only offer if we have an uncompressed version,
  //  check to see 
  HyperLogLog *estimator;
  Data_Get_Struct(self, HyperLogLog, estimator);
  
  uword32 x = hyperloglog_hash(item);
  uword32 j = x >> (32 - estimator->bits);
  uword32 r = hyperloglog_clz( (x << estimator->bits) | (1 << (estimator->bits - 1)) + 1 );
  
  if(hyperloglog_get_register(estimator->registers, j) < r) {
    hyperloglog_set_register(estimator->registers, j, r);
    return Qtrue;
  } else {
    return Qfalse;
  }
}

extern "C" VALUE hyperloglog_serialize() {
  // compress the boolArray to an EWAH
  return Qnil;
}

extern "C" VALUE hyperloglog_deserialize(VALUE serialized) {
  // create a new hyperlolog and set the EWAH
  return Qnil;
}

// Merges a bunch of serialized hyperloglogs
extern "C" VALUE hyperestimator_merge(VALUE args) {
  // merge a bunch of things and return a set of registers
  //   What is it that we're merging here? A bunch of EWAHs I'd imagine
  return Qnil;
}

// class function
extern "C" VALUE hyperestimator_estimate_many(VALUE args) {
  // merge args and then estimate
  VALUE merged = hyperestimator_merge(args);
  
  // var r_sum = 0
  // for(var j = 0; j < registers.count; j++) {
  //   r_sum += Math.pow(2, (-1 * registers.get(j)))
  // }
  // 
  // // for registerCount >= 128 (bits >= 7)
  // var alpha_m = 0.7213 / (1 + 1.079 / registers.count)
  // var estimate = alpha_m * Math.pow(registers.count, 2) * (1 / r_sum)
  // 
  // if(estimate <= (5.0/2.0) * registers.count) {
  //   // Small Range Estimate
  //   var zeros = 0.0
  //   for(var z = 0; z < registers.count; z++) {
  //     if(registers.get(z) == 0) { zeros++ }
  //   }
  //   return Math.round(registers.count * Math.log(registers.count / zeros))
  // } else if(estimate <= (1.0/30.0) * Math.pow(2, 32)) {
  //   // Intermedia Range Estimate
  //   return Math.round(estimate)
  // } else if(estimate > (1.0/30.0) * Math.pow(2, 32)) {
  //   // Large Range Estimate
  //   return Math.round( (Math.pow(-2, 32) * Math.log(1 - (estimate / Math.pow(2, 32)))) )
  // }
  
  return Qnil;
}

// static VALUE rbHyperLogLog;
// static VALUE rbHyperEstimator;
// extern "C" void Init_hyperloglog() {
//   rbHyperLogLog = rb_define_class("HyperLogLog", rb_cObject);
//   rb_define_singleton_method(rbHyperLogLog, "new", (ruby_method*) &hyperloglog_new, 0);
//   rb_define_method(rbHyperLogLog, "initialize", (ruby_method*) &hyperloglog_init, 0);
//   rb_define_method(rbHyperLogLog, "offset", (ruby_method*) &hyperloglog_offer, 1);
//
//   rbHyperEstimator = rb_define_class("HyperEstimator", rb_cObject);
//   rb_define_singleton_method(rbHyperEstimator, "merge", (ruby_method*) &hyperloglog_merge, -2);
//   rb_define_singleton_method(rbHyperEstimator, "estimate", (ruby_method*) &hyperloglog_estimate_many, -2);
// }