# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "hyperloglog"
  s.version = "0.0.1"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.2") if s.respond_to? :required_rubygems_version=
  s.authors = ["Josh Ferguson"]
  s.date = "2012-04-26"
  s.description = "An efficient implementation of the HyperLogLog cardinality estimator"
  s.email = "josh@besquared.net"
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = ["CHANGELOG", "README.md", "ext/boolarray.h", "ext/ewah.h", "ext/extconf.rb", "ext/hyperloglog.cpp", "ext/murmur3.h"]
  s.files = ["CHANGELOG", "Manifest", "README.md", "Rakefile", "ext/boolarray.h", "ext/ewah.h", "ext/extconf.rb", "ext/hyperloglog.cpp", "ext/murmur3.h", "spec/data/integers.txt", "spec/data/small_integers.txt", "spec/data/small_integers2.txt", "spec/hyperloglog_spec.rb", "spec/spec.opts", "hyperloglog.gemspec"]
  s.homepage = "http://www.github.com/besquared/hyperloglog/"
  s.rdoc_options = ["--line-numbers", "--inline-source", "--title", "Hyperloglog", "--main", "README.md"]
  s.require_paths = ["lib", "ext"]
  s.rubyforge_project = "hyperloglog"
  s.rubygems_version = "1.8.15"
  s.summary = "An efficient implementation of the HyperLogLog cardinality estimator"

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
    else
    end
  else
  end
end
