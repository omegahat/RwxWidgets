#!/usr/bin/perl -w 
use GCC::TranslationUnit; 
use GCC::Node::XML; 
use XML::Simple; 
 
my $file = shift @ARGV || "t/record.c.tu"; 
my $root = GCC::TranslationUnit::Parser->parsefile($file)->root; 
 
my $xml = $root->xmllist; 
print XMLout($xml, RootName => 'API'); 
