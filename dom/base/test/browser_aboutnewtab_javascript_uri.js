/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

// Ensure that the preloaded browser exists, and it's finished loading.
async function ensurePreloaded(gBrowser) {
  gBrowser._createPreloadBrowser();
  // We cannot use the regular BrowserTestUtils helper for waiting here, since that
  // would try to insert the preloaded browser, which would only break things.
  await BrowserTestUtils.waitForCondition( () => {
    return gBrowser._preloadedBrowser.contentDocument.readyState == "complete";
  });
}

// The test case verifies that loading javascript: URL in a preloaded browser
// wouldn't cause process switching (by checking outerWindowID).
add_task(async function() {
  await ensurePreloaded(gBrowser);
  await BrowserTestUtils.withNewTab({gBrowser, opening: BROWSER_NEW_TAB_URL, waitForLoad: false}, async function(browser) {

    // Before loading javascript:
    let outerWindowID = browser.outerWindowID;
    await ContentTask.spawn(browser, [BROWSER_NEW_TAB_URL], function([BROWSER_NEW_TAB_URL]) {
      is(content.document.documentURI, BROWSER_NEW_TAB_URL, "verify documentURI");
      is(content.document.querySelector("#test"), undefined, "verify that document has not been modified yet");
    });

    let locationChangePromise = BrowserTestUtils.waitForLocationChange(gBrowser, BROWSER_NEW_TAB_URL);
    // <div id="test"></div>
    browser.loadURI("javascript:'%3Cdiv%20id%3D%22test%22%3E%3C%2Fdiv%3E';");
    await locationChangePromise;

    // After loaded javascript:
    is(browser.outerWindowID, outerWindowID, "verify that the outerWindow didn't change");
    await ContentTask.spawn(browser, [BROWSER_NEW_TAB_URL], function([BROWSER_NEW_TAB_URL]) {
      is(content.document.documentURI, BROWSER_NEW_TAB_URL, "verify documentURI");
      ok(content.document.querySelector("#test"), "verify that document has been modified")
    });
  });
});
