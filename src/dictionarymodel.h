#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include "dictionarymetadata.h"
#include "heinzelnissemodel.h"
#include "dictccimportermodel.h"

#include <QAbstractListModel>
#include <QSettings>
#include <QSqlDatabase>

class DictionaryModel : public QAbstractListModel
{
    Q_OBJECT
public:

    static const QString settingDictionaryId;
    static const QString settingRemainingHints;
    static const QString heinzelnisseId;
    static const QString heinzelnisseLanguages;
    static const QString heinzelnisseTimestamp;
    static const int currentMetadataVersion;

    DictionaryModel();

    virtual int rowCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    HeinzelnisseModel heinzelnisseModel;
    DictCCImporterModel dictCCImporterModel;

    Q_INVOKABLE void selectDictionary(int dictionaryIndex);
    Q_INVOKABLE void deleteSelectedDictionary();
    Q_INVOKABLE QString getSelectedDictionaryName();
    Q_INVOKABLE QString getSelectedDictionaryId();
    Q_INVOKABLE int getSelectedDictionaryIndex();
    Q_INVOKABLE bool isInteractionHintDisplayed();

public slots:
    void handleModelChanged();

signals:
    void dictionaryChanged();
    void deletionNotSuccessful(const QString &dictionaryId);

private:
    QString readLanguages(QSqlDatabase &database);
    QString readTimestamp(QSqlDatabase &database);
    void initializeDatabases();

    QList<DictionaryMetadata*> availableDictionaries;
    int selectedIndex;
    DictionaryMetadata* selectedDictionary;
    QSettings settings;
};

#endif // DICTIONARYMODEL_H
