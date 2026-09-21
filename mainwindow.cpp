#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStack>
#include <QStringList>

static const char *treeData = R"(
0|Jeremiah O'Neal|AKA_TE324543
1|Dudley McCabe|TG943760
2|Lester McCabe|TG708346
3|Alice S Elliott|TG492705
4|Elizabeth McQuiston|TG270541
5|Charles McQuiston|TG804631
6|Charles McQuistion|TG972783
6|Rebecca Grannis|TG168177
5|Mary Thorpe|TG295740
6|Mary Jane Sumner|TG333041
6|William Thorpe|TG594126
4|James N Elliott|TG654890
5|James Elliott|TG673245, TG749502
6|Margaret Scott|TG771250
5|Margaret Elliott|TG182976
6|Frederika Regkukel|TG178840
6|Johann Jacob Friedrich Huber|TG895038
3|John McCabe|TG628417
4|Edward Mccabe|TG307645
5|James McCabe|TG654147
5|Mary|TG812186
4|Sarah McAvoy|TG918273
5|James McAvoy|TG891052
6|John McAvoy|TG151970
6|Sarah Ann McAvoy|TG932996
5|Rosamund Sloan|TG540918
6|Ann McGowan|TG724442
6|John Sloan|TG857477
2|Noma Vade Smith|TG315902
3|Archie T Smith|TG713289
4|Albert Franklin Smith|TG839162
5|John Isaac Smith|TG917384
6|Lucy Ann Kreidler|TG863497
6|William Smith|TG257997
5|Ruanna Hamilton|TG463829
6|Sarah Elizabeth Marlow|TG122353
6|Thomas Cleophas Hamilton|TG407091
4|Rose Ann Prickett|TG501784
5|Adaline A Holderman|TG356814
6|Jacob Holderman Sr|TG847654
6|Mercy Caroline Loveland|TG663974
5|Charles Prickett|TG728195
6|James Prickett|TG124971
6|Rebecca Wisham|TG408693
3|Polly Myrtle Bowman|TG856134
4|Nancy Jane Lambert|TG348671
5|Aaron Lorenzo Lambert|TG684510
6|Henry Ira Lambert|TG780558
6|Sarah 'Sally' M Craven|TG866463
5|Tabitha Ann Brown|TG370924
6|John W Brown|TG718808
6|Nancy Jan Wilhite|TG999320
4|Thomas S Bowman|TG962430
5|Abel Bowman|TG940672
6|George W Bowman Jr|TG587699
6|Mary Catherine Eisenhower|TG296993
5|Mary Martha Shumaker|TG215839
6|Jemima Blunk|TG394660
6|Thomas J Shoemake|TG413298
1|Natalie|TG264819
2|Minnie Schlorff|TG742018
3|Mary Johannsen|TG324786
4|Elena M Johannsen|TG654173
5|Lorenz Hinrichsen|TG702543
5|Sophia Margaretha Hinrichsen|TG404787
4|Johannsen|TG323932
3|William John Ludwig Sclorf|TG916000
2|Percy W Shapley|TG739123
3|Amelia B Hetdke|TG984215
4|Amelia Kiehlbauch|TG472690
5|Barbara Beck|TG835097
6|Barbara Maier/Beck|TG513452
6|Constantin Beck|TG268612
5|Josef Kiehlbauch|TG274361
6|Johanna Knoepfle|TG171824
6|Joseph Sr Kiehlbauch|TG453802
4|Robert R Hedtke|TG903148
5|Amelia Carolina Luedtke|TG610982
5|August Friedrich Hedtke|TG923450
6|Florentine Henriette Florence Hedtke|TG413360
6|Johann E Hedtke|TG842378
3|Burke C Maynard|TG239670
4|Gail Agnes Hillman|TG286753
5|Agnes Maria Platt|TG148675
6|David C Platt|TG158342
6|Miranda McLane|TG112471
5|Fred Ernest Hillman|TG796320
6|Levi Colburn Hillman|TG415161
6|Mary Marinda Shelly|TG759722
4|William R Maynard|TG715094
5|George Maynard|TG859743
6|Sarah Parsons|TG500791
6|William Maynard|TG564843
5|Margaret Rose Sansom|TG502168
6|Riley Sansom|TG563953
6|Sarah Sally Kline|TG208743
)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTreeWidget *tree = ui->treeWidget;

    struct StackItem {
        int depth;
        QTreeWidgetItem *item;
    };
    QStack<StackItem> stack;

    for (const QString &line : QString::fromUtf8(treeData).split('\n')) {
        if (line.trimmed().isEmpty())
            continue;

        int bar1 = line.indexOf('|');
        int bar2 = line.indexOf('|', bar1 + 1);
        if (bar1 < 0 || bar2 < 0)
            continue;

        int depth = line.left(bar1).toInt();
        QString name = line.mid(bar1 + 1, bar2 - bar1 - 1);
        QString tg = line.mid(bar2 + 1);

        while (!stack.isEmpty() && stack.top().depth >= depth)
            stack.pop();

        QTreeWidgetItem *item = stack.isEmpty()
            ? new QTreeWidgetItem(tree)
            : new QTreeWidgetItem(stack.top().item);

        item->setText(0, name);
        item->setText(1, tg);

        stack.push({depth, item});
    }

    tree->expandAll();
    tree->resizeColumnToContents(0);
    tree->resizeColumnToContents(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
