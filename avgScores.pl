#!/usr/bin/perl -w
#

my $sum = 0;
my $count = 0;
my $max = 0; 
my $time = 0.0; 

while ($line = <>)
{
   chomp($line);
   if ($line =~ /Final Score:\s*(\d+)/)
   {
      $sum += $1;
      $count++;
      $max = ($1 > $max) ? $1 : $max
   }
   if ($line =~ /Average turn time:\s*(\d+\.\d+e?[-+]?\d+)/)
   {
      $time += $1; 
   }
}

print "Number Items : ", $count, "\n"; 
print "Average Score: ", $sum/$count, "\n";
print "Maximum Score: ", $max, "\n";
print "Average Time : ", $time/$count, "\n";
