%%bonnie={'A4' 'F#5' 'E5' 'D5' 'E5' 'D5' 'B4' 'A4'}
%% Assume BPM=200 for Bonnie *|=0.3 second long
clear all;
Fs=8000;
dur = 0.3*Fs; %% Time for 1/4 note
z=zeros(1,200); %% Zero buffer between 
A4 =  sin(2*pi* [1:dur]/Fs * 440); %% A4
FS5=  sin(2*pi* [1:dur]/Fs * 739); %% F sharp 5
E5 =  sin(2*pi* [1:dur]/Fs * 659); %% E5
D5 =  sin(2*pi* [1:dur]/Fs * 587); %% D5
B4 =  sin(2*pi* [1:dur]/Fs * 493); %% B4
C5 =  sin(2*pi* [1:dur]/Fs * 523); %% C5
G4 =  sin(2*pi* [1:dur]/Fs * 392); %% G4
F5 =  sin(2*pi* [1:dur]/Fs * 698); %% F5
C4 =  sin(2*pi* [1:dur]/Fs * 261); %% C4
E4 =  sin(2*pi* [1:dur]/Fs * 329); %% E4
D4 =  sin(2*pi* [1:dur]/Fs * 293); %% D4
F4 =  sin(2*pi* [1:dur]/Fs * 349); %% F4
bonnie  =   [A4 z FS5 z E5 z  D5 z E5 z D5 z B4 z A4]; 
furelise  =   [E5 z D5 z E5 z  D5 z E5 z B4 z D5 z A4]; 
praeludium = [G4 z C5 z E5 z  A4 z D5 z F5 z C4 z E4 z G4 z C5 z E5 z  A4 z D5 z F5 z C4 z E4 z G4 z C5 z E5 z  A4 z D5 z F5 z C4 z E4 z G4 z C5 z E5 z  A4 z D5 z F5 z C4 z E4];
hallelujah = [C4 z A4 z C4 z A4 z C4 z A4 z C4 z A4 z F4 z C4 z G4 z C4 z G4 z C4 z F4 z G4]; 
while(1)
    inp=input("1: Fur Elise\n2: Praeludium\n3: Hallelujah\n4: Bonnie\nChoose a song:");
    switch inp
        case 1
            soundsc(furelise, Fs)
            spectrogram(furelise,256,250,256,Fs,'yaxis');
            title('Spectrogram Fur Elise by SAJ')
            print('furelise','-dpng')
            audiowrite('fureliseSine.wav',furelise,Fs) % Write the audio 
        case 2
            soundsc(praeludium, Fs)
            spectrogram(praeludium,256,250,256,Fs,'yaxis');
            title('Spectrogram Praeludium by SAJ')
            print('praeludium2','-dpng')
            audiowrite('praeludiumSine.wav',praeludium,Fs) % Write the audio 
        case 3
            soundsc(hallelujah, Fs)
            spectrogram(hallelujah,256,250,256,Fs,'yaxis');
            title('Spectrogram Hallelujah by SAJ')
            print('hallelujah2','-dpng')
            audiowrite('hallelujahSine.wav',hallelujah,Fs) % Write the audio 
        case 4
            soundsc(bonnie, Fs)
            spectrogram(bonnie,256,250,256,Fs,'yaxis');
            title('Spectrogram Bonnie by SAJ')
            print('bonnie2','-dpng')
            audiowrite('bonnieSine.wav',bonnie,Fs) % Write the audio 
        case q
            break;
    end        
            
    
    
end    
