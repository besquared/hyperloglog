require 'lib/hyperloglog'

describe 'A HyperBuilder' do
  before(:each) do
    @builder = HyperBuilder.new(11)
    0.upto(9) {|index| @builder.offer(index.to_s)}
  end
  
  it 'should put to_s' do
    puts @builder.to_s
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
end

describe 'A HyperEstimator with a small set' do
  before(:each) do
    @builder = HyperBuilder.new(11)
    0.upto(9){ |index| @builder.offer(index.to_s) }
  end
  
  it 'should generate great estimates for a single estimator' do
    puts HyperEstimator.estimate(@builder.estimator)
  end
end