#!/usr/bin/perl -w

my $sum = 0;
my $count = 0;
my $max = 0; 
my $min = 4080;
my $time = 0.0; 

while ($line = <>)
{
   chomp($line);
   if ($line =~ /Final Score:\s*(\d+)/)
   {
      $sum += $1;
      $count++;
      $max = ($1 > $max) ? $1 : $max;
      $min = ($1 < $min) ? $1 : $min;
   }
   if ($line =~ /Average turn time:\s*(\d+\.\d+e?[-+]?\d+)/)
   {
      $time += $1; 
   }
}

print $min, "\n";
print $sum/$count, "\n";
print $max, "\n";
