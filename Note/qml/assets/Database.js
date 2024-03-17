function dbInit()
{
    console.log("dbInit")

    var db = LocalStorage.openDatabaseSync("note_db", "", "Track exercise", 1000000)
    try {
        db.transaction(function (tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS note (id INTEGER PRIMARY KEY AUTOINCREMENT, date TEXT NOT NULL, text TEXT NOT NULL)')
        })
    } catch (err) {
        console.log("Error creating table in database: " + err)
    };
}

function dbGetHandle()
{
    console.log("dbGetHandle")

    try {
        var db = LocalStorage.openDatabaseSync("note_db", "",
                                               "Track exercise", 1000000)
    } catch (err) {
        console.log("Error opening database: " + err)
    }
    return db
}

function dbInsert(Pdate, Ptext)
{
    console.log("dbInsert")

    var db = dbGetHandle()
    var rowid = 0;
    db.transaction(function (tx) {
        tx.executeSql('INSERT INTO note (date, text) VALUES(?, ?)', [Pdate, Ptext])
        var result = tx.executeSql('SELECT last_insert_rowid()')
        rowid = result.insertId
    })
    return rowid;
}

function dbUpdate(Pid, Pdate, Ptext)
{
    console.log("dbUpdate")

    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql('UPDATE note SET date = ?, text = ? WHERE id = ?', [Pdate, Ptext, Pid])
    })
}

function dbRemove(id)
{
    console.log("dbRemove")

    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql('DELETE FROM note WHERE id = ?',[id])
    })
}

function dbReadAll()
{
    console.log("dbReadAll")

    var db = dbGetHandle()
    noteModel.clear()

    db.transaction(function (tx) {
        var results = tx.executeSql('SELECT id, date, text FROM note order by date desc')
        for (var i = 0; i < results.rows.length; i++) {
            var item = results.rows.item(i)
            console.log("id from sql: " + item.id)
            noteModel.append({
                                 noteId: item.id,
                                 noteDate: item.date,
                                 noteText: item.text
                             })
        }
    })
}
