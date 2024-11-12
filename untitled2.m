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
plot(x, sqrt_math, 'b-', 'DisplayName', 'sqrt(x)', 'LineWidth', 2); % Plot sqrt(x) in blue
plot(x, sqrt_fast, 'r--', 'DisplayName', 'fast_sqrt(x)', 'LineWidth', 2); % Plot fast_sqrt(x) in red

% Adding labels and title
xlabel('x');
ylabel('Value');
title('Comparison of sqrt(x) and fast sqrt(x)');
legend show; % Show the legend
grid on; % Add grid for better readability
hold off; % Release the hold

% Set a threshold to reject small values
threshold = 1e-10;

% Create a mask for the values that are greater than the threshold for difference
mask = abs(difference) > threshold;

% Create a new array for the filtered difference
filtered_difference = difference(mask);
filtered_x = x(mask);

% Second figure: Plotting the difference
figure;
plot(filtered_x, filtered_difference, 'g-', 'DisplayName', 'Difference', 'LineWidth', 2); 
xlabel('X-axis Label'); % Replace with appropriate label
ylabel('Difference Signal'); % Replace with appropriate label
title('Filtered Difference Plot');
legend show; % Show the legend
grid on; % Optional: add a grid for better visibility

% Calculate relative error
relative_error = abs(sqrt_math - sqrt_fast) ./ abs(sqrt_math);

% Create a mask for the relative error values greater than the threshold
mask_error = relative_error > threshold;

% Create a new array for the filtered relative error
filtered_relative_error = relative_error(mask_error);
filtered_x_error = x(mask_error);

% Third figure: Plotting the relative error
figure;
plot(filtered_x_error, filtered_relative_error, 'm-', 'DisplayName', 'Relative Error'); % Plot relative error in magenta

% Adding labels and title for the relative error plot
xlabel('x');
ylabel('Relative Error');
title('Relative Error between sqrt(x) and fast sqrt(x)');
legend show; % Show the legend
grid on; % Add grid for better readability
mean_absolute_error = mean(abs(relative_error)) % Calculate MAE

%% RMS 
% Parameters
close;
clear;
clc;
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
harmonic_amplitude = 330;    % Amplitude of the harmonic signal
harmonic_signal = harmonic_amplitude * sin(2 * pi * harmonic_frequency * t);
add_signal = 0 * sin(2 * pi * 350 * t);
% Combined signal (fundamental + harmonic)
combined_signal = sinusoidal_signal + harmonic_signal + add_signal;

% Plot the combined signal
figure;
plot(t, combined_signal);
xlabel('Time (seconds)');
ylabel('Amplitude');
title('Combined Sinusoidal Signal (Fundamental + Harmonic)');
grid on;
% Define noise level as a percentage of the amplitude
noise_level = 0.05 * amplitude; % For example, 5% of the amplitude

% Generate white Gaussian noise
noise = noise_level * randn(size(combined_signal));

% Add noise to the combined signal
noisy_combined_signal = combined_signal + noise;

% Plot the original and noisy signals for comparison
figure;
subplot(2, 1, 1);
plot(t, combined_signal, 'b', 'DisplayName', 'Combined Signal');
xlabel('Time (s)');
ylabel('Amplitude');
title('Original Combined Signal (Fundamental + Harmonic)');
legend;

subplot(2, 1, 2);
plot(t, noisy_combined_signal, 'r', 'DisplayName', 'Noisy Combined Signal');
xlabel('Time (s)');
ylabel('Amplitude');
title('Noisy Combined Signal');
legend;
% Perform FFT on the combined signal
N = length(noisy_combined_signal);         % Number of samples
Y = fft(noisy_combined_signal);            % FFT of the combined signal
P2 = abs(Y / N);                     % Two-sided spectrum
P1 = P2(1:N/2+1);                    % Single-sided spectrum
P1(2:end-1) = 2 * P1(2:end-1);

% Frequency axis
f = fs * (0:(N/2)) / N;

% Extract the amplitudes of the fundamental and harmonic frequencies
fundamental_amplitude = P1(f == frequency);   % Amplitude at 50 Hz (fundamental)
harmonic_amplitudes = P1(f > frequency & f <= harmonic_frequency * 3);  % Amplitudes of harmonics

% Calculate the total harmonic distortion (THD)
thd = sqrt(sum(harmonic_amplitudes.^2)) / fundamental_amplitude;

% Display the THD
fprintf('THD = %.6f%%\n', thd * 100);

% Define buffer size
BUFFER_SIZE = 200;         % Size of the buffer for RMS calculations

% Initialize RMS buffer
rms_buffer = zeros(1, BUFFER_SIZE); % Initialize RMS buffer

function rms = RMS(signal_actual, RMS_handler, BUFFER_SIZE)
    % Define constants
    ONE_BY_BUFFERSIZE = 1 / BUFFER_SIZE;

    % Persistent variables to store data across function calls
    persistent rms_buffer signal_integral buffer_overflow buffr_pointr;

    % Initialize persistent variables
    if isempty(rms_buffer)
        rms_buffer = zeros(RMS_handler, BUFFER_SIZE);
        signal_integral = zeros(1, RMS_handler);
        buffer_overflow = zeros(1, RMS_handler, 'logical');
        buffr_pointr = ones(1, RMS_handler);
    end

    % Calculate signal square
    signal_x2 = signal_actual^2;

    % Update integral and buffer pointer if overflow
    if buffer_overflow(RMS_handler)
        signal_integral(RMS_handler) = signal_integral(RMS_handler) - rms_buffer(RMS_handler, buffr_pointr(RMS_handler));
    end

    % Store the squared signal in the buffer
    rms_buffer(RMS_handler, buffr_pointr(RMS_handler)) = signal_x2;
    signal_integral(RMS_handler) = signal_integral(RMS_handler) + signal_x2;

    % Increment and reset buffer pointer if needed
    buffr_pointr(RMS_handler) = buffr_pointr(RMS_handler) + 1;
    if buffr_pointr(RMS_handler) > BUFFER_SIZE
        buffr_pointr(RMS_handler) = 1;
        buffer_overflow(RMS_handler) = true;
    end

    % Calculate the RMS value
    rms = sqrt(ONE_BY_BUFFERSIZE * signal_integral(RMS_handler));
end


function rms = rapid_RMS(signal_actual, RMS_handler, BUFFER_SIZE)
    % Define constants
    ONE_BY_BUFFERSIZE = 1 / BUFFER_SIZE;
    FAST_RMS_COEF = 1.109890;

    % Persistent variables to store data across function calls
    persistent rms_buffer signal_integral buffer_overflow buffr_pointr;

    % Initialize persistent variables
    if isempty(rms_buffer)
        rms_buffer = zeros(RMS_handler, BUFFER_SIZE);
        signal_integral = zeros(1, RMS_handler);
        buffer_overflow = zeros(1, RMS_handler, 'logical');
        buffr_pointr = ones(1, RMS_handler);
    end

    % Calculate scaled absolute value of the signal
    signal_fabs = abs(signal_actual) * ONE_BY_BUFFERSIZE;

    % Update integral and buffer pointer if overflow
    if buffer_overflow(RMS_handler)
        signal_integral(RMS_handler) = signal_integral(RMS_handler) - rms_buffer(RMS_handler, buffr_pointr(RMS_handler));
    end

    % Store the absolute value in the buffer
    rms_buffer(RMS_handler, buffr_pointr(RMS_handler)) = signal_fabs;
    signal_integral(RMS_handler) = signal_integral(RMS_handler) + signal_fabs;

    % Increment and reset buffer pointer if needed
    buffr_pointr(RMS_handler) = buffr_pointr(RMS_handler) + 1;
    if buffr_pointr(RMS_handler) > BUFFER_SIZE
        buffr_pointr(RMS_handler) = 1;
        buffer_overflow(RMS_handler) = true;
    end

    % Calculate the rapid RMS (using FAST_RMS_COEF for ideal sinusoidal signals)
    rms = signal_integral(RMS_handler) * FAST_RMS_COEF;
end


% Define parameters
BUFFER_SIZE = 200; % Define the buffer size based on your needs
L = length(combined_signal); % Length of the signal
RMS_handler = 1; % RMS handler index (if using multiple handlers, adjust accordingly)

% Initialize arrays for RMS values
rms_values = zeros(1, L);
rapid_rms_values = zeros(1, L);

% Calculate RMS values for each element in the sinusoidal signal
for i = 1:L
    rms_values(i) = RMS(noisy_combined_signal(i), RMS_handler, BUFFER_SIZE); % Calculate normal RMS
    rapid_rms_values(i) = rapid_RMS(noisy_combined_signal(i), RMS_handler, BUFFER_SIZE); % Calculate rapid RMS
end

% Display the final RMS values
NormalRMS = rms_values(end);
RapidRMS = rapid_rms_values(end);
errorRMS = abs(NormalRMS - RapidRMS) / NormalRMS

% Optional: Plotting the results for comparison
figure;
hold on;
plot(noisy_combined_signal, 'g-', 'DisplayName', 'Sinusoidal Signal', 'LineWidth', 2); % Plot signal
plot(rms_values, 'b-', 'DisplayName', 'Normal RMS', 'LineWidth', 2); % Normal RMS
plot(rapid_rms_values, 'r--', 'DisplayName', 'Rapid RMS', 'LineWidth', 2); % Rapid RMS
xlabel('Sample Index');
ylabel('RMS Value');
title('Comparison of Normal RMS and Rapid RMS');
legend show;
grid on;
hold off;

%% Plotting THD vs. Relative Error

% Data for THD and Relative Error
THD = [0.0, 1.3, 3.0, 6.1, 15.2, 18.4, 23.9, 45.0, 98.0];  % THD values in %
Relative_Error = [0.083, 0.3, 1.1, 1.8, 3.7, 4.4, 4.6, 4.7, 5.1]; % Relative Error values in %

% Plotting the data
figure;
plot(THD, Relative_Error, 'bo-', 'LineWidth', 2, 'MarkerSize', 6); % Blue line with circle markers

% Adding labels, title, and grid
xlabel('THD [%]');
ylabel('Relative Error [%]');
title('THD vs. Relative Error');
grid on; % Add grid for readability

% Optional: Displaying data points on the plot
for i = 1:length(THD)
    text(THD(i), Relative_Error(i),THD(i), ...
         'HorizontalAlignment', 'center');
end

%% DFT
% Define file names
files = {'P1_values.csv', 'P2_values.csv', 'P3_values.csv', 'P4_values.csv'};

% Initialize cell arrays to store frequency bins and amplitudes for each file
frequencies = cell(1, 4);
amplitudes = cell(1, 4);

% Factors for dividing frequency bins for each file
divisors = [1, 2, 5, 10];

% Loop through each file and read the data
for i = 1:length(files)
    % Read the CSV file
    data = readtable(files{i});
    
    % Display variable names for troubleshooting
    disp(['Variable names in ', files{i}, ':']);
    disp(data.Properties.VariableNames);
    
    % Extract data columns based on variable names
    freqColName = data.Properties.VariableNames{1}; % First column name
    ampColName = data.Properties.VariableNames{2}; % Second column name
    
    % Apply divisor to frequency column and store
    frequencies{i} = data.(freqColName) / divisors(i);
    amplitudes{i} = data.(ampColName);
end

% Plot the data
figure;
hold on;
colors = {'r', 'g', 'b', 'k'}; % Colors for each line
labels = {'1n', '0.5n', '0.2n', '0.1n'}; % Labels for legend

for i = 1:length(files)
    plot(frequencies{i}, amplitudes{i}, 'Color', colors{i}, 'DisplayName', labels{i}, 'LineWidth', 2);
end

% Add labels and title
xlabel('Frequency Bin');
ylabel('Amplitude');
title('Amplitude vs DFT resolution 1, 2, 5, and 10');
legend;
grid on;
hold off;

%% Taylor
% Define the range of x from -pi to pi
x = linspace(-pi, pi, 1000);

% Calculate the true sine values
y_sin = sin(x);

% Calculate the Taylor series approximation up to the x^9/9! term
y_taylor = x - (x.^3 / factorial(3)) + (x.^5 / factorial(5)) ...
           - (x.^7 / factorial(7)) + (x.^9 / factorial(9));

% Plot both functions
figure;
plot(x, y_sin, 'b-', 'LineWidth', 1.5); hold on;
plot(x, y_taylor, 'r--', 'LineWidth', 1.5);

% Add labels and title
xlabel('x (radians)');
ylabel('Value');
title('Comparison of sin(x) and Taylor Series Approximation');

% Add legend
legend('sin(x)', 'Taylor Series Approximation', 'Location', 'Best');

% Show grid for better visualization
grid on;

% Release hold on the plot
hold off;
