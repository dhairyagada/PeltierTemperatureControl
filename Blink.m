
ClearCom
s = serial('COM3','BaudRate', 9600);
set(s,'Timeout',120); 
time=2000;
i=1;
x_time=[0:1.5:150];
while(i<time)

    fopen(s);
    fprintf(s, 'Your serial data goes here')
    
    out  = fscanf(s)
    out2 = fscanf(s)
    %%out3 = fscanf(s);
    DHTemp(i)=str2num(out(1:2))
    
    %% 
    subplot(211);
    plot(DHTemp,'g');
    set(gca,'XTick',[0:1.5:150])
    axis([0,150,10,65]);
    title('DHT11 Temperature');
    xlabel('Time');
    ylabel('Temperature');
    grid
    
    SETemp(i)=str2num(out2(1:2))
    subplot(212);
    plot(SETemp,'m');
    set(gca,'XTick',[0:1.5:150])
    axis([0,150,10,65]);
    title('Set Temperature');
    xlabel('Time');
    ylabel('Temperature ');
    grid
    
    
   
    i=i+1;
    drawnow;
end
fclose(s)
delete(s)
clear s