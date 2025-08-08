while true
  pause(0.05);
  tsl = fopen("tsl", "r");
  flag = fread(tsl);
  fclose(tsl);
  if flag == 48
    m = load("out.mat");
    contour(m.M_matrix, 50);
    colormap("jet")
    tsl = fopen("tsl", "w");
    fwrite(tsl, "1");
    fclose(tsl);
  endif
endwhile
