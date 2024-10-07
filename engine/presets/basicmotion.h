#pragma once
#include "galaction.h"
#include "gameitem.h"
#include <QString>
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
  ChangeCharacterAction(const Character& hide, const Character& show, qreal time = 0);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }

  Character hide;
  Character show;
  qreal time;
};

class OneShakeAction: public GalAction {
public:
  OneShakeAction(const QString &target, const CharacterTransform& base = {}, qreal time = 1000);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }

  QString target;
  CharacterTransform base;
  qreal time;
};
} // namespace GalEngine