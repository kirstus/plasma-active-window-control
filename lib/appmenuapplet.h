/*
 * Copyright 2016 Kai Uwe Broulik <kde@privat.broulik.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <Plasma/Applet>
#include <QPointer>

class KDBusMenuImporter;
class QQuickItem;
class QMenu;
class AppMenuModel;

class AppMenuApplet : public Plasma::Applet
{
    Q_OBJECT

    Q_PROPERTY(AppMenuModel* model READ model WRITE setModel NOTIFY modelChanged)

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    Q_PROPERTY(int view READ view WRITE setView NOTIFY viewChanged)

    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)

    Q_PROPERTY(QQuickItem *buttonGrid READ buttonGrid WRITE setButtonGrid NOTIFY buttonGridChanged)

    Q_PROPERTY(QString auroraeThemePath READ auroraeThemePath NOTIFY auroraeThemePathChanged)

    Q_PROPERTY(QString auroraeThemeType READ auroraeThemeType NOTIFY auroraeThemeTypeChanged)

public:
    enum ViewType {
        FullView,
        CompactView
    };

    explicit AppMenuApplet(QObject *parent, const QVariantList &data);
    ~AppMenuApplet() override;

    void init() override;

    int currentIndex() const;

    QQuickItem *buttonGrid() const;
    void setButtonGrid(QQuickItem *buttonGrid);

    AppMenuModel *model() const;
    void setModel(AppMenuModel *model);

    bool enabled() const;
    void setEnabled(bool enabled);

    int view() const;
    void setView(int type);

    void registerService();
    void unregisterService();

    QString auroraeThemePath() const;
    QString auroraeThemeType() const;
    Q_INVOKABLE QString extensionForTheme(const QString &themeDirectoryPath);
    Q_INVOKABLE QString translateThemePath(const QString &themeDirectoryPath);
    Q_INVOKABLE void refreshAuroraeTheme();

signals:
    void modelChanged();
    void enabledChanged();
    void viewChanged();
    void currentIndexChanged();
    void buttonGridChanged();
    void requestActivateIndex(int index);
    void auroraeThemePathChanged();
    void auroraeThemeTypeChanged();

public slots:
    void trigger(QQuickItem *ctx, int idx);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QMenu *createMenu(int idx) const;
    void setCurrentIndex(int currentIndex);
    void onMenuAboutToHide();

    int m_currentIndex = -1;
    bool m_enabled = false;
    int m_viewType = FullView;
    QPointer<QMenu> m_currentMenu;
    QPointer<QQuickItem> m_buttonGrid;
    QPointer<AppMenuModel> m_model;
    static int s_refs;
    QString m_auroraeDecorationPath = QString();
    QString m_auroraeDecorationType = QString("svg");
};
