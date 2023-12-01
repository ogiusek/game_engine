class CameraFollow : public ScriptBase
{
  void Update(Object *object, PerFrameProps *props) override
  {
    Object *parent = object->get<VectorTree>().getParent(1);
    Transform2D tf = parent->get<Transform2D>(Transform2D());
    tf.x = object->get<Transform2D>().x - (props->window->w / 2);
    tf.y = object->get<Transform2D>().y - (props->window->h / 2);
    parent->set(tf);
  }

  void Draw(Object *object, PerFrameProps *props) override {}
};