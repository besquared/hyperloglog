require 'echoe'
require 'rake'
require 'rspec/core/rake_task'

task :default => :spec

Echoe.new("hyperloglog") do |p|
  p.author = "Josh Ferguson"
  p.email = "josh@besquared.net"
  p.project = "hyperloglog"
  p.summary = "An efficient implementation of the HyperLogLog cardinality estimator"
  p.url = "http://www.github.com/besquared/hyperloglog/"
end

RSpec::Core::RakeTask.new(:spec) do |t|
  t.pattern = 'spec/**/*_spec.rb'
  t.rspec_opts = ['--options', "\"spec/spec.opts\""]
end