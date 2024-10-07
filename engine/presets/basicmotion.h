#pragma once
#include "galaction.h"
#include "gameitem.h"
#include <QString>
#include <QStringList>
namespace GalEngine {
class FadeInAction : public GalAction {
public:
  FadeInAction(const QString &target, const CharacterTransform &base = {},
               qreal time = 1000);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }

  QString target;
  CharacterTransform base;
  qreal time;
};

class ChangeCharacterAction : public GalAction {
public:
  ChangeCharacterAction(const Character &hide, const Character &show,
                        qreal time = 0);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }

  Character hide;
  Character show;
  qreal time;
};

class OneShakeAction : public GalAction {
public:
  OneShakeAction(const QString &target, const CharacterTransform &base = {},
                 qreal time = 1000);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }

  QString target;
  CharacterTransform base;
  qreal time;
};

class ChoiceAction : public GalAction {
public:
  ChoiceAction();
  ChoiceAction &addChoice(const QString &choice, const QString &jump);
  ChoiceAction &operator()(const QString &choice, const QString &jump);

  bool clog() const override { return true; }
  void execute(IGameHandler *handler) override;

private:
  QStringList choices;
  QStringList labels;
};
} // namespace GalEngine