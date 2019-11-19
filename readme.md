# Implementujte jednoduchou střílecí hru alespoň jednoho hráče proti počítači.

## Hra musí splňovat následující funkcionality:

 Objekty, které je možné zničit (nepřátelské jednotky, statické barikády)
 Pohybovat s hráčem (chůze panáčka, let vesmírné lodi, páčka na odrážení míčků)
 Po zničení objektu s určitou pravděpodobností zůstane bonus, implementujte několik různých bonusů (munice, rychlejší nabíjení,...)
 Implementujte jednoduchý "fyzikální" model (setrvačnost lodi, gravitace, odrážení, nabíjení zbrani,...)
 Implementujte načítání (generátoru) mapy ze souboru a ukládání nejlepších skóre do souboru.

## Kde lze využít polymorfismus? (doporučené)

 Rozdělení objektů: (ne)pohyblivý, hráč vs. nepřítel
 Různé bonusy: munice, silnější zbraně, zdvojení zbraní, rychlejší přebíjení,...
 Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...
 Další informace

https://cs.wikipedia.org/wiki/Arkanoid
https://www.arcade-history.com/?n=ace-invaders&page=detail&id=115810
https://en.wikipedia.org/wiki/Asteroids_(video_game)
https://en.wikipedia.org/wiki/Tank_Battalion

Tato úloha je hodnocena automatem a následně vyučujícím. Nejprve úlohu odevzdejte a odlaďte na automatu, pak jedno Vámi vybrané řešení předejte k ohodnocení vyučujícím. Předání úlohy k hodnocení učitelem se provede tlačítkem "Předat vyučujícímu" u zvoleného řešení. Vyučující bude hodnotit pouze jedno Vaše řešení, vyučující nezačně hodnotit dokud mu úlohu nepčředáte. Dokud není úloha ohodnocena jak automatem tak i učitelem, nejsou přidělené žádné body (jsou zobrazována pouze dílčí hodnocení v procentech).

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vlastni popis

Hra bude ve stylu bulanku nicmene v tomto pripde nepratele nebudou moci strilet a zabiji hrace na dotek;
Hrac ma moznost strilet s urcitou kadenci, kdyz trefi nepritele, tak ho znici a z nepreitele s urcitou pravdepodonosti muze vypadnout bonus,
ktery po sebranim hracem modifikuje hracovy vlastnosti. Bud muze pridat hraci rychlost pohybu nebo kadenci strileni.

Hrac se bude pohybovat klavesmay a w s d a strilet bude mezernikem.

Hrac ani nepratele nebudou schopni prochazet zdmy a kulka se po kontaktu s jakymkoli jinym objektem znici. Nepratele a hrac se po dotyku se zdi zastavi.
Dotek se zdi zpusobi jejich zastaveni.

Polymorfismus bude vyuzit pro manipulaci s hernimi udalostmi 

Nacitani mapy bude z textoveho souboru, kde bude mozno specifikovat jednotlive polohy nepratel, zdi a hrace
