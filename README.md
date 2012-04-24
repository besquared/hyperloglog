# HyperLogLog for Ruby

HyperLogLog is an algorithm for estimating the cardinality of a set. The HyperLogLog strategy has several nice properties:

1. It is near-optimal in its estimation ability
2. allows you some coarse tuning on the amount of standard error you can tolerate
3. The data structures that are used for the estimation are fast, easily compressed and stored, and can be recombined to provide estimates of both the union and intersection of multiple sets

The API is broken out into 2 pieces, the HyperBuilder and the HyperEstimator. This is done for clarity as well as performance optimizations in the future.

# Installation

    gem install hyperloglog

# Example
    
    # Build a new estimator
    builder = HyperBuilder.new
    0.upto(100).each{|user_id| builder.offer(user_id.to_s)}
    
    # Read an estimator from bytes on disk
    estimator = HyperEstimator.new(File.read('bytes.txt'))
    
    # Estimate the union of our two sources
    estimate = HyperEstimator.estimate(builder.estimator, estimator)
    
    # puts estimate
    # => 147
    
# External Libraries Included

Murmur3
https://github.com/PeterScott/murmur3

EWAHBoolArray
https://github.com/lemire/EWAHBoolArray
