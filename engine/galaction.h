#pragma once
#include <qtypes.h>
namespace GalEngine {
class IGameHandler;
class Game;
class GalAction {
  friend Game;

public:
  virtual void execute(IGameHandler *handler) = 0;
  virtual bool clog() const { return true; }
  virtual ~GalAction() = default;
  qsizetype index() const { return index_; }

private:
  qsizetype index_;
};
} // namespace GalEngine