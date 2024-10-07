#include "stage.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

namespace GalEngineView {

ShowCharacterItem::ShowCharacterItem(QQuickItem *parent) : QQuickItem(parent) {}
ShowCharacterItem::~ShowCharacterItem() = default;

QAnimationGroup *ShowCharacterItem::createAnimationsFromTransform(
    const GalEngine::CharacterTransform &oldT,
    const GalEngine::CharacterTransform &newT, qreal time, int type) {

  auto group = new QParallelAnimationGroup();
  if (oldT.opacity != newT.opacity) {
    auto animation =
        createCharacterAnimation(oldT.opacity, newT.opacity, time, type);
    animation->setPropertyName("opacity");
    animation->setTargetObject(this);
    group->addAnimation(animation);
  }
  if (oldT.angle != newT.angle) {
    auto animation =
        createCharacterAnimation(oldT.angle, newT.angle, time, type);
    animation->setPropertyName("rotation");
    animation->setTargetObject(this);
    group->addAnimation(animation);
  }
  if (oldT.pos != newT.pos) {
    auto animation = createCharacterAnimation(oldT.pos, newT.pos, time, type);
    animation->setPropertyName("location");
    animation->setTargetObject(this);
    group->addAnimation(animation);
  }
  if (oldT.scale != newT.scale) {
    auto animation = createCharacterAnimation(oldT.pos, newT.pos, time, type);
    animation->setPropertyName("scale");
    animation->setTargetObject(this);
    group->addAnimation(animation);
  }
  return group;
}

QPropertyAnimation *ShowCharacterItem::createCharacterAnimation(
    const QVariant &start, const QVariant &end, qreal time, int type) const {
  Q_UNUSED(type);
  auto result = new QPropertyAnimation();
  result->setStartValue(start);
  result->setEndValue(end);
  result->setDuration(time);
  return result;
}

QPointF ShowCharacterItem::location() const { return location_; }

void ShowCharacterItem::setLocation(const QPointF &p) {
  if (p == location_) {
    return;
  }
  location_ = p;
  emit locationChanged();
}
QString ShowCharacterItem::url() const { return image_url_; }

void ShowCharacterItem::setUrl(const QString &u) {
  if (image_url_ == u) {
    return;
  }
  image_url_ = u;
  emit urlChanged();
}

void ShowCharacterItem::applyTransform(const GalEngine::CharacterTransform &t) {
  this->setLocation(t.pos);
  this->setRotation(t.angle);
  this->setScale(t.scale);
  this->setOpacity(t.opacity);
}

// ------------Stage-------------

Stage::Stage(QQuickItem *parent) : QQuickItem(parent) {
  animation_ = new QParallelAnimationGroup(this);
  connect(animation_, &QAbstractAnimation::stateChanged,
          [this](const QAbstractAnimation::State &newState,
                 const QAbstractAnimation::State &oldState) {
            if (oldState == QAbstractAnimation::Running &&
                newState == QAbstractAnimation::Stopped) {
              emit transformingChanged();
            }
            if (oldState == QAbstractAnimation::Stopped &&
                newState == QAbstractAnimation::Running) {
              emit transformingChanged();
            }
          });
}

QQmlListProperty<ShowCharacterItem> Stage::showCharacters() {
  return QQmlListProperty<ShowCharacterItem>(this, this, &Stage::characterCount,
                                             &Stage::characterAt);
}

QList<ShowCharacterItem *> Stage::originShowCharacters() const {
  return this->show_characters_;
}

ShowCharacterItem *Stage::characterAt(QQmlListProperty<ShowCharacterItem> *list,
                                      qsizetype index) {
  auto *stage = static_cast<Stage *>(list->object);
  Q_ASSERT(index >= 0 && index < stage->show_characters_.size());
  return stage->show_characters_.at(index);
}

qsizetype Stage::characterCount(QQmlListProperty<ShowCharacterItem> *list) {
  auto *stage = static_cast<Stage *>(list->object);
  return stage->show_characters_.size();
}

void Stage::addCharacter(const GalEngine::Character &c) {
  this->characters_.append(c);
  auto shownCharacter = new ShowCharacterItem(this);
  shownCharacter->applyTransform(c.transform);
  shownCharacter->setUrl(c.imageUrl);
  show_characters_.append(shownCharacter);
  emit showCharactersChanged();
}

QList<GalEngine::Character> Stage::characters() const { return characters_; }
GalEngine::Character &Stage::characterAt(qsizetype i) { return characters_[i]; }

void Stage::startTransform(
    const QString &target,
    std::optional<GalEngine::CharacterTransform> startState) {
  for (int i = 0; i < characters_.size(); i++) {
    auto &c = characters_[i];
    auto &cs = show_characters_[i];
    if (c.imageUrl == target) {
      if (startState.has_value()) {
        c.transform = startState.value();
      }
      temp_transform_state.insert(target, new QSequentialAnimationGroup());
      return;
    }
  }
}

void Stage::addTransform(const QString &target,
                         const GalEngine::CharacterTransform &t, qreal during,
                         int type) {
  for (int i = 0; i < characters_.size(); i++) {
    auto &c = characters_[i];
    auto &cs = show_characters_[i];
    if (c.imageUrl == target) {
      auto animation =
          cs->createAnimationsFromTransform(c.transform, t, during, type);
      auto group = temp_transform_state[target];
      group->addAnimation(animation);
      c.transform = t;
      return;
    }
  }
}

void Stage::finishTransform() {
  if (transforming()) {
    animation_->stop();
  }
  animation_->clear();
  for (auto &t : temp_transform_state) {
    animation_->addAnimation(t);
  }
  temp_transform_state.clear();
  animation_->start();
}

bool Stage::transforming() const {
  return animation_->state() == QAbstractAnimation::Running;
}

void Stage::skip() {
  if (transforming()) {
    animation_->stop();
  }

  animation_->clear();
  for (int i = 0; i < characters_.size(); i++) {
    auto &c = characters_[i];
    auto &cs = show_characters_[i];
    cs->applyTransform(c.transform);
  }
}
} // namespace GalEngineView