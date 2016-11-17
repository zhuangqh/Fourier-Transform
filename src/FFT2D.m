function destImg = fft2d( img, op )
% op: 1 DFT
% op: -1 IDFT

[height, width] = size(img);

padHeight = 2^nextpow2(height);
padWidth = 2^nextpow2(width);

img = double(img);
% zero padding
destImg = padarray(img, [padHeight - height, padWidth - width], 0, 'post');

% horizon
for x = 1:padHeight;
    % reverse-bits
    j = padWidth / 2;
    i = 1;
    while i < padWidth - 1;
        if i < j;
            tmp = destImg(x, i + 1);
            destImg(x, i + 1) = destImg(x, j + 1);
            destImg(x, j + 1) = tmp;
        end
        k = padWidth / 2;
        while j >= k;
            j = j - k;
            k = k / 2;
        end
        
        j = j + k;
        i = i + 1;
    end
    
    % compute
    T = 2;
    while T <= padWidth;
        Wn = complex(cos(op*2*pi / T), sin(op*2*pi / T));
        
        i = 0;
        while i < padWidth;
            W = 1;
            
            j = i;
            while j < i + T / 2;
                u = destImg(x, j + 1);
                v = W * destImg(x, j + T / 2 + 1);
                
                destImg(x, j + 1) = u + v;
                destImg(x, j + T / 2 + 1) = u - v;
                W = W * Wn;
                
                j = j + 1;
            end
            i = i + T;
        end
        T = T * 2;
    end
    
    if op == 1; % IDFT
        destImg(x) = destImg(x) / padWidth;
    end
end

% vertical
for y = 1:padWidth;
    % reverse-bits
    j = padHeight / 2;
    i = 1;
    while i < padHeight - 1;
        if i < j;
            tmp = destImg(i + 1, y);
            destImg(i + 1, y) = destImg(j + 1, y);
            destImg(j + 1, y) = tmp;
        end
        k = padHeight / 2;
        while j >= k;
            j = j - k;
            k = k / 2;
        end
        
        j = j + k;
        i = i + 1;
    end
    
    % compute
    T = 2;
    while T <= padHeight;
        Wn = complex(cos(op*2*pi / T), sin(op*2*pi / T));
        
        i = 0;
        while i < padHeight;
            W = 1;
            
            j = i;
            while j < i + T / 2;
                u = destImg(j + 1, y);
                v = W * destImg(j + T / 2 + 1, y);
                
                destImg(j + 1, y) = u + v;
                destImg(j + T / 2 + 1, y) = u - v;
                W = W * Wn;
                
                j = j + 1;
            end
            i = i + T;
        end
        T = T * 2;
    end

    if op == 1; % IDFT
        destImg(:, y) = destImg(:, y) / padHeight;
    end
end

% greater sight
if op == -1;
    imgShow = fftshift(destImg); % Center FFT
else
    imgShow = destImg;
end

imgShow = abs(imgShow); % Get the magnitude
imgShow = log(imgShow+1); % Use log, for perceptual scaling, and +1 since log(0) is undefined
imgShow = mat2gray(imgShow); % Use mat2gray to scale the image between 0 and 1

imgShow = uint8(imgShow*255);
imshow(imgShow,[]); % Display the result

end
