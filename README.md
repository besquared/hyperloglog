# HyperLogLog for Ruby

# External Libraries Included

Murmur3
https://github.com/PeterScott/murmur3

EWAHBoolArray
https://github.com/lemire/EWAHBoolArray

# Example
    
    # Build a new estimator
    builder = HyperBuilder.new
    0.upto(100).each{|user_id| builder.offer(user_id)}
    
    # Read an estimator from bytes on disk
    estimator = HyperEstimator.new(File.read('bytes.txt'))
    
    # Union and estimate from our two sources
    estimate = HyperEstimator.estimate(builder.estimator, estimator)