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
      items.each {|item| builder.offer(item.to_s)}

      estimate = HyperEstimator.estimate(builder.estimator)

      # puts "For m = #{m} we should have #{estimate} in [#{total_items - (3 * se)}, #{total_items + (3 * se)}]"
      estimate.should be >= total_items - (3 * se)
      estimate.should be <= total_items + (3 * se)
    end
  end

  it 'should merge estimators' do
    items = load_data('small_integers')
    total_items = items.uniq.length

    items_a = items[0, items.count*0.75]
    items_b = items[items.count*0.5, items.count*0.5]

    4.upto(20) do |m|
      se = total_items * (1.04 / Math.sqrt(2**m))

      builder_a = HyperBuilder.new(m)
      builder_b = HyperBuilder.new(m)
      items_a.each {|item| builder_a.offer(item.to_s)}
      items_b.each {|item| builder_b.offer(item.to_s)}

      estimate = HyperEstimator.estimate(builder_a.estimator, builder_b.estimator)

      # puts "For m = #{m} we should have #{estimate} in [#{total_items - (3 * se)}, #{total_items + (3 * se)}]"
      estimate.should be >= total_items - (3 * se)
      estimate.should be <= total_items + (3 * se)
    end
  end
end
