clc
clear

syms y(t)
sympref('FloatingPointOutput',true)

outputFilePath = "../Samples/third-order.txt";
file = fopen(outputFilePath, 'r');

% Reads the first line which should be the coeffecients of the diff.eq.
% Parses the line as an array of doubles
coefficient_line = strtrim(fgetl(file));
coefficient_array = strsplit(coefficient_line);
coefficients = reshape(str2double(coefficient_array), 1, [])

% Reads the second line which should be the initial conditions
% Parses the line as an array of doubles, too.
initial_conditions_line = strtrim(fgetl(file));
initial_conditions_array = strsplit(initial_conditions_line);
initial_conditions = reshape(str2double(initial_conditions_array), 1, [])

% With the cursor position still correct,
% Reads the rest of the file as the sampled points from C++
sampled_values = fscanf(file, "%f %f", [2 Inf]);
fclose(file);

% Reads the file as 2 rows, INF cols.
% Transpose for INF rows, 2 cols.
sampled_values = transpose(sampled_values); 
[rowC, colC] = size(sampled_values);

% Generate the same diff.eq. in matlab.
[ignore, order] = size(coefficients); % assume diff.eq. order = # of coefficients

eq = diff(y, t, order);
conditions = sym("a",[1 order]);
for i = 1:order
    diffYofi = diff(y, t, i - 1);

    eq = eq + coefficients(i) * diffYofi;
    condition = diffYofi(0) == initial_conditions(i);

    conditions(i) = condition;
end
diffSolution(t) = simplify(dsolve(eq, conditions))

% Handle graphs
startTime = sampled_values(1, 1)
endTime = sampled_values(end, 1)

tiledlayout(3, 1)
timeDomain = linspace(startTime, endTime, 1000);
diffFunction = diffSolution(timeDomain);

nexttile
hold on
plot(timeDomain, diffFunction, 'b')
plot(sampled_values(:,1), sampled_values(:,2), 'r:', 'LineWidth', 1.5)
title("MatLab Generated & C++ Sampled Diff. Eq.")
ylabel("y(t)")
xlabel("t")
legend('MatLab Function','C++ Approximation')
hold off

nexttile 
plot(timeDomain, diffFunction, 'b')
title("MatLab Generated Diff. Eq.")
ylabel("y(t)")
xlabel("t")
legend('MatLab Function')

nexttile
plot(sampled_values(:,1), sampled_values(:,2), 'r:', 'LineWidth', 1.5)
title("C++ Sampled Diff. Eq.")
ylabel("y(t)")
xlabel("t")
legend('C++ Approximation')