#pragma once
#include <QQuickImageProvider>
namespace GalEngine {
class CharacterImageProvider : public QQuickImageProvider {
public:
  CharacterImageProvider(ImageType type, Flags flags = Flags());
  QImage requestImage(const QString &id, QSize *size,
                      const QSize &requestedSize) override;
  void addCharacter(const QString &nameUrl, QImage image);

private:
  QHash<QString, QImage> assets;
  static constexpr const char* icon_name = "icon";
  static constexpr const char* stand_name = "stand";
};
} // namespace GalEngine