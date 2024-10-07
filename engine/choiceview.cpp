#include "choiceview.h"
namespace GalEngineView {
ChoiceView::ChoiceView(QQuickItem *parent) : QQuickItem(parent) {
  setVisible(false);
}
QStringList ChoiceView::choices() const { return choices_; }
void ChoiceView::closeAndClear() {
  setVisible(false);
  choices_.clear();
  labels_.clear();
  emit choicesChanged();
}

void ChoiceView::addChoice(const QString &choice, const QString& label) {
  choices_.append(choice);
  labels_.append(label);
  if (this->choices_.size() == 1 && !this->isVisible()) {
    setVisible(true);
  }
  emit choicesChanged();
}

} // namespace GalEngineView