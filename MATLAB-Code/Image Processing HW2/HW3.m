fig=1;

f= fopen('ct_scan-1.bin');
ct=fread(f,[256,256],"uint8");

figure(fig); fig=fig+1;
imshow(ct);

ct=~ct;
figure(fig); fig=fig+1;
imshow(ct);


CC = bwconncomp(ct);
numPixels = cellfun(@numel,CC.PixelIdxList);
[biggest,idx] = max(numPixels);
ct(CC.PixelIdxList{idx}) = 0;
figure(fig); fig=fig+1;
imshow(~ct);
figure(fig); fig=fig+1;
imshow(ct);