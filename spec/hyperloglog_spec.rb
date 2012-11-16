$LOAD_PATH << '.'
require 'lib/hyperloglog'

def load_data(name)
  File.readlines(File.join(File.dirname(__FILE__), 'data', "#{name}.txt"))
end

describe 'A HyperBuilder' do
  before(:each) do
    @builder = HyperBuilder.new(11)
    0.upto(9) {|index| @builder.offer(index.to_s)}
  end

  it 'should put to_s' do
    @builder.to_s.should_not == nil
  end

  it 'should serialize' do
    @builder.serialize.should_not == nil
  end

  it 'should generate an estimator' do
    @builder.estimator.should_not == nil
  end

  it 'should create the proper estimator' do
    @builder.to_s.should == @builder.estimator.to_s
  end

  it 'should reset' do
    @builder.reset
    @builder.size_in_bits.should == 0
  end
end

describe 'A HyperEstimator' do
  it 'should generate good estimates' do
    items = load_data('small_integers')
    total_items = items.uniq.length

    4.upto(20) do |m|
      se = total_items * (1.04 / Math.sqrt(2**m))

      builder = HyperBuilder.new(m)
      items.each{|item| builder.offer(item.to_s)}

      estimate = HyperEstimator.estimate(builder.estimator)

      # puts "For m = #{m} we should have #{estimate} in [#{total_items - (3 * se)}, #{total_items + (3 * se)}]"
      estimate.should be >= total_items - (3 * se)
      estimate.should be <= total_items + (3 * se)
    end
  end
end
