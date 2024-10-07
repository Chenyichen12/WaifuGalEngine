#pragma once
#include <QQuickItem>
#include <QStringList>
namespace GalEngineView {
class ChoiceView : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(QStringList choices READ choices NOTIFY choicesChanged)
public:
  ChoiceView(QQuickItem *parent = nullptr);
  QStringList choices() const;
  void closeAndClear();
  void addChoice(const QString& choice, const QString& label = "");
  QStringList labels() const { return labels_; }
signals:
  void choicesChanged();
  void choose(int index);

private:
  QStringList choices_;
  QStringList labels_;
};
} // namespace GalEngineView