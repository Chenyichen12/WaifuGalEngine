#pragma once
#include <QPointF>
#include <QString>

namespace GalEngine {
struct Sentence {
  QString text;
  QString who;
  std::optional<QString> imageUrl;
  Sentence(const QString &text, const QString &who);
};

struct CharacterTransform {
  QPointF pos = {0.5, 0};
  qreal angle = 0;
  qreal scale = 1;
  qreal opacity = 1;
};

struct Character {
  CharacterTransform transform;
  QString imageUrl;
  Character(const QString &url, const CharacterTransform &t);
};
} // namespace GalEngine
