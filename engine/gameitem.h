#pragma once
#include <QPointF>
#include <QString>

namespace GalEngine {
struct Sentence {
  QString text;
  QString who;
  std::optional<QString> imageUrl;
  Sentence(const QString &text, const QString &who);
  Sentence();

  Sentence say(const QString& text) const;
  Sentence by(const QString& who) const;
  Sentence show(const QString& url) const;

};

struct CharacterTransform {
  QPointF pos = {0.5, 0};
  qreal angle = 0;
  qreal scale = 1;
  qreal opacity = 1;

  CharacterTransform move(qreal x, qreal y) const;
  CharacterTransform rotate(qreal angle) const;
  CharacterTransform zoom(qreal scale) const;
  CharacterTransform fade(qreal opacity) const;
};

struct Character {
  CharacterTransform transform;
  QString imageUrl;
  Character(const QString &url, const CharacterTransform &t);
};
} // namespace GalEngine
