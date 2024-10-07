#include "textbar.h"
#include <QPropertyAnimation>
namespace GalEngineView {

class TextTransform : public QPropertyAnimation {
public:
  TextTransform(TextBar *bar) : QPropertyAnimation(bar, "showText") {}
  QVariant interpolated(const QVariant &from, const QVariant &to,
                        qreal progress) const override {
    Q_UNUSED(from)
    auto endStr = to.toString();
    int whichIndex = endStr.size() * progress;
    return endStr.mid(0, whichIndex);
  }
};
TextBar::TextBar(QQuickItem *parent) : QQuickItem(parent) {
  text_animation_ = new TextTransform(this);
}
QString TextBar::showText() const { return showtext_; }
void TextBar::setShowText(const QString &showText) {
  if (showText == showtext_) {
    return;
  }
  showtext_ = showText;
  emit showTextChanged();
}

bool TextBar::showing() const {
  return text_animation_->state() == QAbstractAnimation::Running;
}

QString TextBar::text() const { return text_; }

void TextBar::setText(const QString &t) {
  text_ = t;
  text_animation_->setStartValue("");
  text_animation_->setEndValue(text_);
  auto during = t.length() * 10;
  text_animation_->setDuration(during);
  text_animation_->start();
}

void TextBar::skip() {
  if (showing()) {
    text_animation_->stop();
  }
  setShowText(text_);
}

QString TextBar::sayingName() const { return saying_name_; }
void TextBar::setSayingName(const QString &name) {
  if (name == saying_name_) {
    return;
  }
  saying_name_ = name;
  emit sayingNameChanged();
}
} // namespace GalEngineView