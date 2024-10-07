#pragma once
#include <QQuickItem>
namespace GalEngineView {
    class TextTransform;
class TextBar : public QQuickItem {
  Q_OBJECT

  Q_PROPERTY(
      QString showText READ showText WRITE setShowText NOTIFY showTextChanged)
  Q_PROPERTY(bool showing READ showing)
  Q_PROPERTY(QString sayingName READ sayingName WRITE setSayingName NOTIFY
                 sayingNameChanged)
public:
  TextBar(QQuickItem *parent = nullptr);
  QString showText() const;
  void setShowText(const QString &showText);
  bool showing() const;

  QString text() const;
  void setText(const QString& t);
  
  QString sayingName() const;
  void setSayingName(const QString& name);
  Q_INVOKABLE void skip();

signals:
  void showTextChanged();
  void sayingNameChanged();
private:
  QString showtext_ = "";
  QString saying_name_ = "";
  QString text_ = "";
  TextTransform *text_animation_;
};
} // namespace GalEngineView