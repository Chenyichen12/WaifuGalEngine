#pragma once
#include "galaction.h"
#include "gameitem.h"
#include <QString>
namespace GalEngine {
class TextAction : public GalAction {
public:
  TextAction(const QString &text);
  TextAction(const Sentence &sentence);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return true; }

  Sentence sentence;
};

class ShowAction : public GalAction {
public:
  ShowAction(const Character &c);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }

  Character character;
};
} // namespace GalEngine