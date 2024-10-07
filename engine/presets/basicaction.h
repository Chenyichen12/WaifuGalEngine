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

class GoToAction : public GalAction {
public:
  GoToAction(const QString &whereToGo);
  void execute(IGameHandler *handler) override;
  bool clog() const override { return false; }
  QString whereToGo;
  std::optional<qsizetype> whereToGoIndex;
};

// do nothing, just for jump to label and move next
class LabelAction : public GalAction {
public:
  LabelAction(const QString &label);
  void execute(IGameHandler *handler) override {}
  bool clog() const override { return false; }
  QString label() const override { return Label; }
  QString Label;
};
} // namespace GalEngine