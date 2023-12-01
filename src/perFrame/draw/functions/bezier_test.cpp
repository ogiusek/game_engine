// void draw_quadratic_bezier(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int x2, int y2)
// {
//   float t;
//   int x, y;
//   for (t = 0; t <= 1; t += 0.01)
//   {
//     x = (1 - t) * (1 - t) * x0 + 2 * (1 - t) * t * x1 + t * t * x2;
//     y = (1 - t) * (1 - t) * y0 + 2 * (1 - t) * t * y1 + t * t * y2;
//     SDL_RenderDrawPoint(renderer, x, y);
//   }
// }
// void draw_quadratic_bezier(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int x2, int y2)
// {
//   float t;
//   int x, y, prev_x, prev_y;
//   float length = 0;
//   float segment_length = 5; // desired length of each line segment
//   for (int i = 0; i < 100; i++)
//   {
//     t = (float)i / 100;
//     x = (1 - t) * (1 - t) * x0 + 2 * (1 - t) * t * x1 + t * t * x2;
//     y = (1 - t) * (1 - t) * y0 + 2 * (1 - t) * t * y1 + t * t * y2;
//     if (i > 0)
//     {
//       float dx = x - prev_x;
//       float dy = y - prev_y;
//       length += sqrt(dx * dx + dy * dy);
//     }
//     prev_x = x;
//     prev_y = y;
//   }
//   int num_steps = length / segment_length;
//   for (int i = 0; i <= num_steps; i++)
//   {
//     t = (float)i / num_steps;
//     x = (1 - t) * (1 - t) * x0 + 2 * (1 - t) * t * x1 + t * t * x2;
//     y = (1 - t) * (1 - t) * y0 + 2 * (1 - t) * t * y1 + t * t * y2;
//     if (i > 0)
//     {
//       SDL_RenderDrawLine(renderer, prev_x, prev_y, x, y);
//     }
//     prev_x = x;
//     prev_y = y;
//   }
// }

// void draw_bezier(SDL_Renderer *renderer, const std::vector<Point> &points)
// {
//   int num_points = points.size();
//   if (num_points < 2)
//     return; // Not enough points to draw a curve

//   auto binomial_coefficient = [](int n, int k) -> int
//   {
//     auto factorial = [](int x) -> int
//     {
//       int result = 1;
//       for (int i = 2; i <= x; i++)
//         result *= i;
//       return result;
//     };
//     return factorial(n) / (factorial(k) * factorial(n - k));
//   };

//   float t;
//   int x, y, prev_x, prev_y;
//   float length = 0;
//   float segment_length = 5; // desired length of each line segment

//   // Calculate the total length of the curve
//   for (int i = 0; i < num_points - 1; i++)
//   {
//     float dx = points[i + 1].x - points[i].x;
//     float dy = points[i + 1].y - points[i].y;
//     length += sqrt(dx * dx + dy * dy);
//   }

//   int num_steps = length / segment_length;

//   // Draw the curve
//   for (int i = 0; i <= num_steps; i++)
//   {
//     t = (float)i / num_steps;
//     x = 0;
//     y = 0;

//     // Calculate the position on the curve using the de Casteljau's algorithm
//     for (int j = 0; j < num_points; j++)
//     {
//       float b = binomial_coefficient(num_points - 1, j) * pow(1 - t, num_points - 1 - j) * pow(t, j);
//       x += b * points[j].x;
//       y += b * points[j].y;
//     }

//     if (i > 0)
//       SDL_RenderDrawLine(renderer, prev_x, prev_y, x, y);

//     prev_x = x;
//     prev_y = y;
//   }
// }
void draw_bezier(SDL_Renderer *renderer, const std::vector<Point> &points)
{
  int num_points = points.size();
  if (num_points < 2)
    return; // Not enough points to draw a curve

  auto binomial_coefficient = [](int n, int k) -> int
  {
    auto factorial = [](int x) -> int
    {
      int result = 1;
      for (int i = 2; i <= x; i++)
        result *= i;
      return result;
    };
    return factorial(n) / (factorial(k) * factorial(n - k));
  };

  float t;
  int x, y, prev_x, prev_y;
  float length = 0;
  float segment_length = 5; // desired length of each line segment

  // Calculate the total length of the curve
  for (int i = 0; i < num_points - 1; i++)
  {
    float dx = points[i + 1].x - points[i].x;
    float dy = points[i + 1].y - points[i].y;
    length += sqrt(dx * dx + dy * dy);
  }

  int num_steps = length / segment_length;

  // Draw the curve
  for (int i = 0; i <= num_steps; i++)
  {
    t = (float)i / num_steps;
    x = 0;
    y = 0;

    // Calculate the position on the curve using the de Casteljau's algorithm
    for (int j = 0; j < num_points; j++)
    {
      float b = binomial_coefficient(num_points - 1, j) * pow(1 - t, num_points - 1 - j) * pow(t, j);
      x += b * points[j].x;
      y += b * points[j].y;
    }

    if (i > 0)
      SDL_RenderDrawLine(renderer, prev_x, prev_y, x, y);

    prev_x = x;
    prev_y = y;
  }
}