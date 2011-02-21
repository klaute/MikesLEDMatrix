#!/usr/bin/perl -w

my $i = 0;
for ( $i = 0; $i < 64; $i++ )
{

	my $k = rand(255);

	print sprintf ( " 0x%02x", $k );

	if ( ($i % 8) == 1 )
	{
#		print "\n";
	}

}

print "\n";

