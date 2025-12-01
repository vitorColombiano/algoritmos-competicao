#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define G 9.80665

int main() {
  double h;
  while (scanf("%lf", &h) == 1) {
    int p1, p2, n;
    scanf("%d %d", &p1, &p2);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
      double alpha, V;
      scanf("%lf %lf", &alpha, &V);

      double alpha_rad = alpha * PI / 180.0;
      double Vx = V * cos(alpha_rad);
      double Vy = V * sin(alpha_rad);

      // Resolve (G/2)t^2 - Vy*t - h = 0
      double a = G / 2.0;
      double b = -Vy;
      double c = -h;
      double delta = b*b - 4*a*c;
      double t = (-b + sqrt(delta)) / (2*a);

      double x = Vx * t;

      printf("%.5lf -> %s\n", x, (x >= p1 && x <= p2) ? "DUCK" : "NUCK");
    }
  }

  return 0;
}
