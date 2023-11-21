class PerFrameProps
{
public:
  Textures *textures = new Textures();
  Window *window;
  FPS *fps;
  Inputs *inputs;

  PerFrameProps(Window *_window, FPS *_fps, Inputs *_inputs) : window(_window), fps(_fps), inputs(_inputs) {}
};