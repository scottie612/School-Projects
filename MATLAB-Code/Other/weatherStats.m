function weatherStats(temps,desc)
    lowerdes=lower(desc);
    high=max(temps);
    
    avg=round(mean(temps));
    sprintf("'Todays' weather was %s , with a high temperature of %i degrees and an average temperature of %i degrees.'",lowerdes,high,avg)
    
   