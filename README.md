# EWAH Bitsets in Ruby

Enhanced Word Aligned Hybrid (EWAH) encoding is a compression strategy for bitmaps. The compressed bitmaps can be scanned over and operated on in place which results in extremely fast processing times even while maintaining high compression rates.

This library wraps the original C++ implementation written by one of the original paper authors Daniel Lemire which is hosted here:

https://github.com/lemire/EWAHBoolArray

The gem is built and tested against ruby 1.8.7. If anyone wants to modify it to also run in ruby 1.9.x I'd gladly accept the pull requests.

To install simply run

    gem install ewah-bitset

Examples are in the spec but the general idea goes something like this:

    require 'ewahbitset'
    
    bitset = EwahBitset.new
    0.upto(10) do |i|
      bitset.set(i * 10)
    end
    
    positions = []
    bitset.each do |position|
      positions << position
    end
    
    puts positions.inspect
    
    => [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    puts bitset.serialize.inspect
    
    => "e\000\000\000\000\000\000\000\003\000\000\000\000\000\000\000\000\000\000\000\004\000\000\000\001\004\020@\000\001\004\020@\000\001\004\020\000\000\000"

# Tradeoffs

Of course there are a few tradeoffs at work here to mention. The first is that bits must be set in order. This means that you can't set bit position 1000 and then go set bit position 100. The other thing to note is that there is no random access into the bitset. Anytime you want to check a set bit you're required to do a sequential scan. Due to this an implemention of is_set? requires a sequential scan using the each method. This may make sense for some uses and not others but be aware!