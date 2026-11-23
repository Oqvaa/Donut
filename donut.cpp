
#include <bits/stdc++.h>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    string opacity = ".,-~:;=!*#$@";

    const int HEIGHT = 40, WIDTH = 120;

    float k1 = 30;
    float scalex = 1.6, scaley = 1;
    float R1 = 1.0, R2 = 2.0;
    float A = 0, B = 0;
    while (true) {
        vector<vector<char>> output(HEIGHT, vector<char>(WIDTH, ' '));
        vector<vector<float>> zbuffer(HEIGHT, vector<float>(WIDTH, INFINITY));
        for (float theta = 0; theta < 2 * M_PI; theta += 0.07) {

            for (float phi = 0; phi < 2 * M_PI; phi += 0.02) {

                float ct = cos(theta);
                float st = sin(theta);

                float cp = cos(phi);
                float sp = sin(phi);

                float x = (R2 + R1 * ct) * cp;
                float y = (R2 + R1 * ct) * sp;
                float z = R1 * st;

                float x1 = x;
                float y1 = y * cos(A) - z * sin(A);
                float z1 = y * sin(A) + z * cos(A);

                float x2 = x1 * cos(B) - y1 * sin(B);
                float y2 = x1 * sin(B) + y1 * cos(B);
                float z2 = z1;

                float depth = z2 + 5;

                if (depth <= 0) continue;

                int xp = WIDTH / 2 + (scalex * k1 * x2) / depth;
                int yp = HEIGHT / 2 - (scaley * k1 * y2) / depth;

                if (xp < 0 || xp >= WIDTH ||
                    yp < 0 || yp >= HEIGHT)
                    continue;

                float luminance = ct * cp;

                int index = max(0, min(
                    (int)(luminance * 5 + 5),
                    (int)opacity.size() - 1
                ));

                // Z-buffer
                if (depth < zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = depth;
                    output[yp][xp] = opacity[index];
                }
            }
        }

        // Render
        cout << "\033[H\033[J";

        for (auto &row : output) {
            for (char c : row)
                cout << c;
            cout << '\n';
        }

        // Update angles
        A += 0.04;
        B += 0.02;

        this_thread::sleep_for(
            chrono::milliseconds(30)
        );
    }

    return 0;
}
