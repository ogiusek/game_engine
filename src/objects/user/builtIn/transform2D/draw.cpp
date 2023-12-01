class DrawTransform2D : public ScriptBase
{
public:
  int32_t r, g, b, a;

  void Update(Object *object, PerFrameProps *props) override {}
  void Draw(Object *object, PerFrameProps *props) override
  {
    Transform2D tf = object->get(Transform2D(0, 0, 0, 0));
    Object *parent = object->get<VectorTree>().getParent();
    while (parent != nullptr)
    {
      Transform2D parentTf = parent->get(Transform2D(0, 0));
      tf.x -= parentTf.x;
      tf.y -= parentTf.y;
      parent = parent->get<VectorTree>().getParent();
    }

    SDL_Rect rect = {(int)tf.x, (int)tf.y, (int)tf.w, (int)tf.h};
    SDL_SetRenderDrawColor(props->window->renderer, r, g, b, a);
    SDL_RenderFillRect(props->window->renderer, &rect);
  }

  DrawTransform2D(ScriptBase sb, int32_t _r = 255, int32_t _g = 255, int32_t _b = 255, int32_t _a = 255)
      : ScriptBase(sb), r(_r), g(_g), b(_b), a(_a) {}
};