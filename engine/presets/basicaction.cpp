#include "presets/basicaction.h"
#include "game.h"
namespace GalEngine {
TextAction::TextAction(const QString &text) : sentence(text, "") {}
TextAction::TextAction(const Sentence &sentence) : sentence(sentence) {}

void TextAction::execute(IGameHandler *handler) { handler->saying(sentence); }

ShowAction::ShowAction(const Character &c) : character(c) {}
void ShowAction::execute(IGameHandler *handler) { handler->show(character); }

GoToAction::GoToAction(const QString &label) : whereToGo(label) {}

void GoToAction::execute(IGameHandler *handler) {
  if (whereToGoIndex.has_value()) {
    handler->moveTo(whereToGoIndex.value());
  } else {
    handler->moveTo(whereToGo);
  }
}

LabelAction::LabelAction(const QString &label) : Label(label) {}

} // namespace GalEngine