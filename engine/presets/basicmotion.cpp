#include "basicmotion.h"
#include "game.h"
namespace GalEngine {
FadeInAction::FadeInAction(const QString &target, const CharacterTransform &b,
                           qreal time)
    : target(target), base(b), time(time) {
  base.opacity = 0;
}
void FadeInAction::execute(IGameHandler *handler) {
  handler->startTransform(target, base);
  auto after = base;
  after.opacity = 1;
  handler->addTransform(target, after, time);
  handler->finishTransform();
}

ChangeCharacterAction::ChangeCharacterAction(const Character &hide,
                                             const Character &show, qreal time)
    : hide(hide), show(show), time(time) {}
void ChangeCharacterAction::execute(IGameHandler *handler) {
  hide.transform.opacity = 1;
  auto hideT = hide.transform;
  hideT.opacity = 0;

  show.transform.opacity = 0;
  auto showT = show.transform;
  showT.opacity = 1;
  handler->startTransform(hide.imageUrl, hide.transform);
  handler->addTransform(hide.imageUrl, hideT, time);
  handler->startTransform(show.imageUrl, show.transform);
  handler->addTransform(show.imageUrl, showT, time);
  handler->finishTransform();
}

OneShakeAction::OneShakeAction(const QString &target,
                               const CharacterTransform &b, qreal time)
    : target(target), base(b), time(time) {}
void OneShakeAction::execute(IGameHandler *handler) {
  auto t1 = base;
  auto t2 = base;
  t1.pos.setX(t1.pos.x() - 0.02);
  t2.pos.setX(t2.pos.x() + 0.02);
  handler->startTransform(target, base);
  handler->addTransform(target, t1, time * 0.25);
  handler->addTransform(target, t2, time * 0.5);
  handler->addTransform(target, base, time * 0.25);
  handler->finishTransform();
}

ChoiceAction::ChoiceAction() {}

ChoiceAction &ChoiceAction::addChoice(const QString &choice,
                                      const QString &label) {
  choices << choice;
  labels << label;
  return *this;
}

ChoiceAction &ChoiceAction::operator()(const QString &choice,
                                       const QString &label) {
  return addChoice(choice, label);
}

void ChoiceAction::execute(IGameHandler *handler) {
  Q_ASSERT(choices.size() != 0);
  handler->showChoices(choices, labels);
}
}; // namespace GalEngine