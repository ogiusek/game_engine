class Nsc : public ScriptBase
{
private:
  float speed = .2;

public:
  void Update(Object *object, PerFrameProps *props) override
  {
    Transform2D tf = object->get(Transform2D(0, 0, 50, 50));
    if (props->inputs->isHeld((int)'w') || props->inputs->isHeld(1073741906))
      tf.y -= props->fps->deltaTime * speed;
    if (props->inputs->isHeld((int)'s') || props->inputs->isHeld(1073741905))
      tf.y += props->fps->deltaTime * speed;
    if (props->inputs->isHeld((int)'a') || props->inputs->isHeld(1073741904))
      tf.x -= props->fps->deltaTime * speed;
    if (props->inputs->isHeld((int)'d') || props->inputs->isHeld(1073741903))
      tf.x += props->fps->deltaTime * speed;

    object->set(tf);
  }

  void Draw(Object *object, PerFrameProps *props) override {}

  Nsc(float _speed) : speed(_speed) {}
};