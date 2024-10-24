clc;
close;
clear
%% Sinus
% Read the data from the CSV file
data = readtable('sine_comparison.csv');

% Extract the data into separate variables
x = data.x;
sin_math = data.sin_x;
sin_mine = data.sin_f_x;
difference = data.Difference;

% Display the first few rows of the data
%disp(data);
% First figure: Plotting sin(x) and sin_f(x)
figure;
hold on; % Hold on to add multiple plots
plot(x, sin_math, 'b-', 'DisplayName', 'sin(x)','LineWidth', 2); % Plot sin(x) in blue
plot(x, sin_mine, 'r-', 'DisplayName', 'MRBsin(x)','LineWidth', 2); % Plot sin_f(x) in red

% Adding labels and title
xlabel('x (radians)');
ylabel('Value');
title('Comparison of sin(x) and MRBsin(x)');
legend show; % Show the legend
grid on; % Add grid for better readability
hold off; % Release the hold

% Second figure: Plotting the difference
figure;
plot(x, difference, 'g-', 'DisplayName', 'Difference'); % Plot the difference in green

% Adding labels and title for the difference plot
xlabel('x (radians)');
ylabel('Difference');
title('Difference between sin(x) and MRBsin(x)');
legend show; % Show the legend
grid on; % Add grid for better readability

% Calculate Mean Absolute Error (MAE)
mean_absolute_error = mean(abs(difference)); % Calculate MAE
fprintf('Mean Absolute Error: %.6f\n', mean_absolute_error); % Display MAE in the command window

%% Cosinus
% Read the data from the CSV file
data = readtable('cosine_comparison.csv');

% Extract the data into separate variables
x = data.x;
cos_math = data.cos_x;
cos_mine = data.cos_f_x;
difference = data.Difference;

% Display the first few rows of the data (optional)
% disp(data);

% First figure: Plotting cos(x) and cos_f(x)
figure;
hold on; % Hold on to add multiple plots
plot(x, cos_math, 'b-', 'DisplayName', 'cos(x)','LineWidth', 2); % Plot cos(x) in blue
plot(x, cos_mine, 'r--', 'DisplayName', 'cosf(x)','LineWidth', 2); % Plot cos_f(x) in red

% Adding labels and title
xlabel('x (radians)');
ylabel('Value');
title('Comparison of cos(x) and cosf(x)');
legend show; % Show the legend
grid on; % Add grid for better readability
hold off; % Release the hold

% Second figure: Plotting the difference
figure;
plot(x, difference, 'g:', 'DisplayName', 'Difference'); % Plot the difference in green

% Adding labels and title for the difference plot
xlabel('x (radians)');
ylabel('Difference');
title('Difference between cos(x) and cosf(x)');
legend show; % Show the legend
grid on; % Add grid for better readability

% Calculate Mean Absolute Error (MAE)
mean_absolute_error = mean(abs(difference)); % Calculate MAE
fprintf('Mean Absolute Error: %.6f\n', mean_absolute_error); % Display MAE in the command window
%% Square Root Comparison
% Read the data from the CSV file
data = readtable('sqrt_comparison.csv');

% Extract the data into separate variables
x = data.x;
sqrt_math = data.sqrt_x;
sqrt_fast = data.fast_sqrt_x;
difference = data.Difference;

% Display the first few rows of the data (optional)
% disp(data);

% First figure: Plotting sqrt(x) and fast_sqrt(x)
figure;
hold on; % Hold on to add multiple plots
plot(x, sqrt_math, 'b-', 'DisplayName', 'sqrt(x)','LineWidth', 2); % Plot sqrt(x) in blue
plot(x, sqrt_fast, 'r--', 'DisplayName', 'fast_sqrt(x)','LineWidth', 2); % Plot fast_sqrt(x) in red

% Adding labels and title
xlabel('x');
ylabel('Value');
title('Comparison of sqrt(x) and fast_sqrt(x)');
legend show; % Show the legend
grid on; % Add grid for better readability
hold off; % Release the hold

% Second figure: Plotting the difference
figure;
plot(x, difference, 'g:', 'DisplayName', 'Difference'); % Plot the difference in green

% Adding labels and title for the difference plot
xlabel('x');
ylabel('Difference');
title('Difference between sqrt(x) and fast_sqrt(x)');
legend show; % Show the legend
grid on; % Add grid for better readability

% Third figure: Plotting the relative error
relative_error = abs(sqrt_math - sqrt_fast) ./ abs(sqrt_math); % Calculate relative error
figure;
plot(x, relative_error, 'm-', 'DisplayName', 'Relative Error'); % Plot relative error in magenta

% Adding labels and title for the relative error plot
xlabel('x');
ylabel('Relative Error');
title('Relative Error between sqrt(x) and fast_sqrt(x)');
legend show; % Show the legend
grid on; % Add grid for better readability

%% RMS 
% Parameters
fs = 10000;                 % Sampling frequency (samples per second)
T = 1/fs;                   % Sampling period (seconds)
frequency = 50;             % Frequency of the base sinusoidal signal in Hz
num_periods = 2;            % Number of periods to generate
L = fs / frequency * num_periods; % Length of the signal for 2 periods
t = (0:L-1) * T;            % Time vector
amplitude = 330;            % Amplitude of the base sinusoidal signal

% Generate the base sinusoidal signal (50 Hz)
sinusoidal_signal = amplitude * sin(2 * pi * frequency * t);

% Add a second sinusoidal signal (harmonic component)
harmonic_frequency = 150;   % Harmonic frequency in Hz (3rd harmonic of 50 Hz)
harmonic_amplitude = 50;    % Amplitude of the harmonic signal
harmonic_signal = harmonic_amplitude * sin(2 * pi * harmonic_frequency * t);

% Combined signal (fundamental + harmonic)
combined_signal = sinusoidal_signal + harmonic_signal;

% Plot the combined signal
figure;
plot(t, combined_signal);
xlabel('Time (seconds)');
ylabel('Amplitude');
title('Combined Sinusoidal Signal (Fundamental + Harmonic)');
grid on;

% Perform FFT on the combined signal
N = length(combined_signal);         % Number of samples
Y = fft(combined_signal);            % FFT of the combined signal
P2 = abs(Y / N);                     % Two-sided spectrum
P1 = P2(1:N/2+1);                    % Single-sided spectrum
P1(2:end-1) = 2 * P1(2:end-1);

% Frequency axis
f = fs * (0:(N/2)) / N;

% Extract the amplitudes of the fundamental and harmonic frequencies
fundamental_amplitude = P1(f == frequency);   % Amplitude at 50 Hz (fundamental)
harmonic_amplitudes = P1(f > frequency & f <= harmonic_frequency * 3);  % Amplitudes of harmonics

% Calculate the total harmonic distortion (THD)
thd = sqrt(sum(harmonic_amplitudes.^2)) / fundamental_amplitude

% Display the THD
fprintf('THD = %.6f%%\n', thd * 100);

% Define buffer size
BUFFER_SIZE = 200;         % Size of the buffer for RMS calculations

% Initialize RMS buffer
rms_buffer = zeros(1, BUFFER_SIZE); % Initialize RMS buffer

% Normal RMS function using persistent variable for buffer
function rms = RMS(signal_actual, BUFFER_SIZE)
    persistent rms_buffer;       % Persistent buffer for RMS
    if isempty(rms_buffer)       % Initialize only once
        rms_buffer = zeros(1, BUFFER_SIZE);
    end
    
    signal_x2 = signal_actual * signal_actual;
    signal_integral = 0;
    
    % Shift the buffer
    for i = 1:BUFFER_SIZE-1
        rms_buffer(i) = rms_buffer(i + 1); % Shift the buffer elements
        signal_integral = signal_integral + rms_buffer(i); % Accumulate the integral
    end
    
    rms_buffer(BUFFER_SIZE) = signal_x2;  % Add new value to buffer
    signal_integral = signal_integral + signal_x2; % Add the current squared signal

    % Calculate RMS
    rms = sqrt((1/BUFFER_SIZE) * signal_integral); % RMS calculation
end

% Rapid RMS function using persistent variable for buffer
function rms = rapid_RMS(signal_actual, BUFFER_SIZE)
    persistent rms_buffer;       % Persistent buffer for rapid RMS
    if isempty(rms_buffer)       % Initialize only once
        rms_buffer = zeros(1, BUFFER_SIZE);
    end
    
    signal_fabs = abs(signal_actual)*0.005; % Absolute value of the signal
    signal_integral = 0;

    % Shift the buffer
    for i = 1:BUFFER_SIZE-1
        rms_buffer(i) = rms_buffer(i + 1); % Shift the buffer elements
        signal_integral = signal_integral + rms_buffer(i); % Accumulate the integral
    end
    
    rms_buffer(BUFFER_SIZE) = signal_fabs;  % Add new value to buffer
    signal_integral = signal_integral + signal_fabs; % Add the absolute value

    % Calculate the rapid RMS coefficient
    FAST_RMS_COEF = 1.109890;  % For ideal sinusoidal signals

    % Return the rapid RMS
    rms = signal_integral * FAST_RMS_COEF; % Rapid RMS calculation
end

% Calculate RMS values for each element in the sinusoidal signal
rms_values = zeros(1, L);
rapid_rms_values = zeros(1, L);
for i = 1:L
    rms_values(i) = RMS(combined_signal(i), BUFFER_SIZE); % Calculate normal RMS
    rapid_rms_values(i) = rapid_RMS(combined_signal(i), BUFFER_SIZE); % Calculate rapid RMS
end

% Display the RMS results
%disp('Index   Normal RMS        Rapid RMS');
NormalRMS = rms_values(end)
RapidRMS = rapid_rms_values(end)
errorRMS = abs(NormalRMS-RapidRMS)/NormalRMS
% Optional: Plotting the results for comparison
figure;
hold on;
plot(combined_signal, 'g-', 'DisplayName', 'Sinusoidal Signal','LineWidth', 2); % Normal RMS
plot(rms_values, 'b-', 'DisplayName', 'Normal RMS','LineWidth', 2); % Normal RMS
plot(rapid_rms_values, 'r--', 'DisplayName', 'Rapid RMS','LineWidth', 2); % Rapid RMS
xlabel('Sample Index');
ylabel('RMS Value');
title('Comparison of Normal RMS and Rapid RMS');
legend show;
grid on;
hold off;  

