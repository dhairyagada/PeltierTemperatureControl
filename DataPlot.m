% Copyright 2014 The MathWorks, Inc.
ClearCom
%% Create serial object for Arduino
s = serial('COM6'); % change the COM Port number as needed
set(s,'Timeout',120); 
%% Connect the serial port to Arduino
%%s.InputBufferSize = 2; % read only one byte every time
try
    fopen(s);
catch err
    fclose(instrfind);
    error('Make sure you select the correct COM Port where the Arduino is connected.');
end
%% Create a figure window to monitor the live data
Tmax = 90; % Total time for data collection (s)
figure,
grid on,
xlabel ('Time (s)'), ylabel('Data (8-bit)'),
axis([0 Tmax+1 -10 300]),
%% Read and plot the data from Arduino
Ts = 1.5; % Sampling time (s)
i = 0;
data = 0;
t = 0;
tic % Start timer

while toc <= Tmax
    i = i + 1;
    %% Read buffer data
    out  = fscanf(s);
    out2 = fscanf(s);
    data(i)=str2num(out(1:2))
    DHTemp(i)=str2num(out(1:2))
    SETemp(i)=str2num(out2(1:2))
    %% Read time stamp
    % If reading faster than sampling rate, force sampling time.
    % If reading slower than sampling rate, nothing can be done. Consider
    % decreasing the set sampling time Ts
    t(i) = toc;
    if i > 1
        T = toc - t(i-1);
        while T < Ts
            T = toc - t(i-1);
        end
    end
    t(i) = toc;
    %% Plot live data
%     if i > 1
%         line([t(i-1) t(i)],[data(i-1) data(i)])
%         drawnow
%     end

    subplot(211);
    plot(DHTemp,'g');
    set(gca,'XTick',[0:1:60])
    axis([0,60,10,65]);
    title('DHT11 Temperature');
    xlabel('Sample n   time=1.5 x n');
    ylabel('Temperature');
    grid


    subplot(212);
    plot(SETemp,'m');
    set(gca,'XTick',[0:1:60])
    axis([0,60,10,65]);
    title('Set Temperature');
    xlabel('Sample n   time=1.5 x n');
    ylabel('Temperature ');
    grid
    drawnow;
end

fclose(s);