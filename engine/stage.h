#pragma once
#include "gameitem.h"
#include <QQuickItem>

class QAnimationGroup;
class QPropertyAnimation;
namespace GalEngineView {

class ShowCharacterItem : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
  Q_PROPERTY(
      QPointF location READ location WRITE setLocation NOTIFY locationChanged)
public:
  ShowCharacterItem(QQuickItem *parent = nullptr);
  ~ShowCharacterItem() override;
  QString url() const;
  void setUrl(const QString &u);

  QPointF location() const;
  void setLocation(const QPointF &p);
  virtual QAnimationGroup *
  createAnimationsFromTransform(const GalEngine::CharacterTransform &oldT,
                                const GalEngine::CharacterTransform &newT,
                                qreal time = 1000, int type = 0);
  // different from doTransform, it will set immediatly
  void applyTransform(const GalEngine::CharacterTransform &t);
signals:
  void locationChanged();
  void urlChanged();

protected:
  virtual QPropertyAnimation *createCharacterAnimation(const QVariant &start,
                                                       const QVariant &end,
                                                       qreal time,
                                                       int type) const;

private:
  QString image_url_;
  QPointF location_;
};
class Stage : public QQuickItem {
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<ShowCharacterItem> showCharacters READ
                 showCharacters NOTIFY showCharactersChanged)
  Q_PROPERTY(bool transforming READ transforming NOTIFY transformingChanged)
public:
  Stage(QQuickItem *parent = nullptr);
  QQmlListProperty<ShowCharacterItem> showCharacters();
  QList<ShowCharacterItem *> originShowCharacters() const;
  QList<GalEngine::Character> characters() const;

  GalEngine::Character &characterAt(qsizetype index);

  void addCharacter(const GalEngine::Character &c);
  void startTransform(const QString &target,
                      std::optional<GalEngine::CharacterTransform> startState);
  void addTransform(const QString &target,
                    const GalEngine::CharacterTransform &t, qreal during,
                    int type = 0);
  void finishTransform();
  Q_INVOKABLE void skip();

  bool transforming() const;
signals:
  void showCharactersChanged();
  void transformingChanged();
private:
  QList<ShowCharacterItem *>
      show_characters_; // the character which show currently
  QList<GalEngine::Character>
      characters_; // the character model. the state of game

  QHash<QString, QAnimationGroup *> temp_transform_state;
  QAnimationGroup *animation_;

  static ShowCharacterItem *
  characterAt(QQmlListProperty<ShowCharacterItem> *list, qsizetype index);
  static qsizetype characterCount(QQmlListProperty<ShowCharacterItem> *list);
};
} // namespace GalEngineView