#!/bin/bash

input_file=$1

awk '
{
    # Split line into metric and value parts
	match($0, /^([^\t0-9]+)[\t ]+\(*([0-9.]+.*)/, a)
    if (RLENGTH > 0) {
        metric = a[1]
        value_str = a[2]
        
        # Extract numeric value (handle different units)
        if (value_str ~ /%$/) {
            # Percentage value
            value = value_str + 0
        }
        else if (value_str ~ /ms$/) {
            # Milliseconds
            value = value_str + 0
        }
        else if (value_str ~ /KB$/) {
            # Kilobytes
            value = value_str + 0
        }
        else {
            # Plain number
            value = value_str + 0
        }
        
        # Store the values
        sums[metric] += value
        counts[metric]++
		metric_value[metric][counts[metric]] = value
    }
}
END {
    printf("%-20s %12s %10s %10s\n", "METRIC", "AVERAGE", "SAMPLES", "VAR")
    print "-----------------------------------------------------------"
    
    # Sort output alphabetically by metric name
    n = asorti(sums, sorted)
    for (i = 1; i <= n; i++) {
        metric = sorted[i]
        avg = sums[metric] / counts[metric]
		var = 0
		for (j = 1; j <= 30; j++) {
			var += (metric_value[metric][j] - avg) * (metric_value[metric][j] - avg)
		}
		var = var / n
		var = sqrt(var)
        printf("%-20s %12.2f %10d %12.2f\n", metric, avg, counts[metric], var)
    }
}' "$input_file"
