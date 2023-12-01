class DrawCircleClass : public ScriptBase
{
public:
  void Update(Object *object, PerFrameProps *props) override {}
  void Draw(Object *object, PerFrameProps *props) override
  {
    Transform2D tf = object->get(Transform2D());
    Transform2D ptf = object->get<VectorTree>().getParent(1)->get(Transform2D());
    int x = tf.x - ptf.x + tf.w / 2,
        y = tf.y - ptf.y + tf.w / 2;
    SDL_SetRenderDrawColor(props->window->renderer, 255, 0, 0, 255);
    DrawFilledCircle(props->window->renderer, x, y, tf.w / 2);
  }
  DrawCircleClass(ScriptBase sb) : ScriptBase(sb) {}
};