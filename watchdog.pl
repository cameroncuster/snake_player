#!/usr/bin/perl -w

 

$str = `ps -e | grep driver`;

chomp($str);

($pid, $port, $time) = ($str =~ /\s*(\d+)\s*(.*?)\s*(..:..:..)\s+driver/);

 

exit(0) if (! defined $pid);

print "Pid $pid $port $time\n";

@parts = split ':', $time;

system("kill -15 $pid") if ($parts[1] > 0);
