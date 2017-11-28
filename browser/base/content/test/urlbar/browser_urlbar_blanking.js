"use strict";

add_task(async function() {
  for (let page of gInitialPages) {
    if (page == "about:newtab") {
      // New tab preloading makes this a pain to test, so skip
      continue;
    }
    let tab = await BrowserTestUtils.openNewForegroundTab(gBrowser, page);
    ok(!gURLBar.value, "The URL bar should be empty if we load a plain " + page + " page.");
    await BrowserTestUtils.removeTab(tab);
  }
});

add_task(async function() {
  // The test was originally to check that reloading of a javascript: URL could
  // throw an error and empty the URL bar. This situation can no longer happen
  // as in bug 836567 we set document.URL to active document's URL on navigation
  // to a javascript: URL; reloading after that will simply reload the original
  // active document rather than the javascript: URL itself. But we can still
  // verify that the URL bar's value is correct.
  const URI = "http://www.example.com/browser/browser/base/content/test/urlbar/file_blank_but_not_blank.html";
  let tab = await BrowserTestUtils.openNewForegroundTab(gBrowser, URI);
  is(gURLBar.value, URI, "The URL bar should match the URI");
  let browserLoaded = BrowserTestUtils.browserLoaded(tab.linkedBrowser);
  ContentTask.spawn(tab.linkedBrowser, null, function() {
    content.document.querySelector("a").click();
  });
  await browserLoaded;
  is(gURLBar.value, URI, "The URL bar should be the previous active document's URI.");
  await ContentTask.spawn(tab.linkedBrowser, null, async function() {
    // This is sync, so by the time we return we should have changed the URL bar.
    content.location.reload();
  });
  is(gURLBar.value, URI, "The URL bar should still be the previous active document's URI.");
  await BrowserTestUtils.removeTab(tab);
  SimpleTest.expectUncaughtException(false);
});
