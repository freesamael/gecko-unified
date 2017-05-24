/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

// Test handling errors in CacheStorage

add_task(function* () {
  // Open the URL in a private browsing window.
  let win = yield BrowserTestUtils.openNewBrowserWindow({ private: true });
  let tab = win.gBrowser.selectedBrowser;
  tab.loadURI(MAIN_DOMAIN + "storage-cache-error.html");
  yield BrowserTestUtils.browserLoaded(tab);

  // On enumerating cache storages, CacheStorage::Keys would throw a
  // DOM security exception. We'd like to verify storage panel still work in
  // this case.
  yield openStoragePanel(null, win.gBrowser);

  const cacheItemId = ["Cache", "http://test2.example.org"];

  yield selectTreeItem(cacheItemId);
  ok(gUI.tree.isSelected(cacheItemId),
    `The item ${cacheItemId.join(" > ")} is present in the tree`);

  yield BrowserTestUtils.closeWindow(win);
  yield finishTests();
});
