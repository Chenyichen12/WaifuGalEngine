#pragma once
#include "gameitem.h"
#include <QQuickItem>

class QAnimationGroup;
namespace GalEngineView {
class TextBar;
class Stage;
} // namespace GalEngineView
namespace GalEngine {
class GalAction;

class IGameHandler {
public:
  virtual void saying(const Sentence &s, int optionFlag = 0) = 0;
  virtual void show(const Character &c, int optionFlag = 0) = 0;

  virtual void startTransform(const QString &nameUrl,
                              const CharacterTransform &start) = 0;
  virtual void startTransform(const QString &nameUrl) = 0;
  virtual void addTransform(const QString &target, const CharacterTransform &t,
                            qreal time, int optionFlag = 0) = 0;
  virtual void finishTransform() = 0;
  // virtual void moveNext() = 0;
  virtual ~IGameHandler() = default;
};

class Game : public QQuickItem, public IGameHandler {
  Q_OBJECT
public:
  GalEngineView::TextBar *textBar() const;
  GalEngineView::Stage *stage() const;
  Game(QQuickItem *parent = nullptr);
  void saying(const Sentence &s, int optionFlag = 0) override;
  void show(const Character &c, int optionFlag = 0) override;

  void startTransform(const QString &nameUrl,
                      const CharacterTransform &start) override;
  void startTransform(const QString &nameUrl) override;
  void addTransform(const QString &target, const CharacterTransform &t,
                    qreal time, int optionFlag = 0) override;
  void finishTransform() override;
  Q_INVOKABLE void moveNext();
  ~Game() override;

  Game& operator<<(GalAction *action);
private:
  GalEngineView::TextBar *textbar;
  GalEngineView::Stage *stage_;
  QList<GalAction*> actions_;
  qsizetype currentActionIndex = 0;
};
} // namespace GalEngine